#include <iostream>
#include <string>
#include <vector>
#include <gcrypt.h>
#include <sstream>
#include <iomanip>

std::string getGcryptError(int32_t errorCode)
{
	char buffer[1024];
	gpg_strerror_r(errorCode, buffer, 1024);
	std::string result(buffer);
	return result;
}

std::string getHexString(const std::vector<uint8_t>& data)
{
	std::ostringstream stringstream;
	stringstream << std::hex << std::setfill('0') << std::uppercase;
	for(std::vector<uint8_t>::const_iterator i = data.begin(); i != data.end(); ++i)
	{
		stringstream << std::setw(2) << (int32_t)(*i);
	}
	stringstream << std::dec;
	return stringstream.str();
}

int main(int argc, char* argv[])
{
	std::string input;
	//  << std::flush should be added
	std::cout << "Enter text to encrypt: ";
	std::getline(std::cin, input);
	if(input.empty())
	{
		std::cerr << "No text entered. Exiting." << std::endl;
		exit(1);
	}
	
	// text length should be checked here as
	// the text should be long enough to be encoded securely
	

	gcry_cipher_hd_t handle = nullptr;
	// gpg_error_t should be used instead of int32_t
	// it's defined as unsigned int in gpg-error.h 
	// ECB mode is insecure, CBC is using chains so it's much safer
	// however CTR mode is safer then CBC as encyption can be parallelized 
	// and can doesn't require any padding
	int32_t result = gcry_cipher_open(&handle, GCRY_CIPHER_AES128, GCRY_CIPHER_MODE_ECB, GCRY_CIPHER_SECURE);
	if(result != GPG_ERR_NO_ERROR)
	{
		std::cerr << "Error initializing handle: " << getGcryptError(result) << std::endl;
		// exit(result) or exit(CUSTOM_ERORR) is more informative;
		exit(1);
	}
	if(!handle)
	{
		std::cerr << "Handle is invalid" << std::endl;
		exit(1);
	}
	
	std::vector<uint8_t> key{ 0x23, 0x53, 0xAA, 0x99, 0x56, 0xB2, 0x0E, 0x91, 0x01, 0x79, 0xCA, 0xEF, 0x42, 0x12, 0x87, 0xB0 };
	result = gcry_cipher_setkey(handle, &key.at(0), key.size());
	if(result != GPG_ERR_NO_ERROR)
	{
		std::cerr << "Error setting key: " << getGcryptError(result) << std::endl;
		// gcry_cipher_close should be called here
		exit(1);
	}
	
	// gcry_cipher_setiv should be used here to achieve semantic security
	// in case of CTR mode gcry_cipher_setctr should be used as well
	std::vector<uint8_t> plain(input.size() % 16 ? input.size() + (16 - (input.size() % 16)) : input.size());
	
	// known padding should be added (to be able to split plain text
	// from random data after decryption
	// buffer overflow should not be the case as plain vector's size 
	// is greater or equeal than input
	memcpy(&plain.at(0), &input.at(0), input.size());
	std::vector<uint8_t> encrypted(plain.size());
	gcry_cipher_encrypt(handle, &encrypted.at(0), encrypted.size(), &plain.at(0), plain.size());
	if(result != GPG_ERR_NO_ERROR)
	{
		std::cerr << "Error encrypting data: " << getGcryptError(result) << std::endl;
		// gcry_cipher_close should be called here
		exit(1);
	}

	std::cout << "Encrypted text: " << getHexString(encrypted) << std::endl;

	gcry_cipher_close(handle);
	return 0;	
}
