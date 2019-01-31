#include <iostream>
#include <string>
#include <vector>
#include <fstream>
// C++ header should be used instead
#include <string.h>

// main1 and main2 are executed on different computers.

int main(int argc, char* argv[])
{
	std::string input;
	//  << std::flush should be added
	std::cout << "Input a number: ";
	std::cin >> input;
	int32_t number = 0;
	try
	{
		number = std::stoi(input);
	}
	// catch block shouldn't be empty, it should handle possible
	// overflows and other integer parsing errors
	catch(std::exception& ex) {}
	
	
	// also the size shouldn't be hardcoded
	// both files should be compled with the same 
	// compiler to make char unsigned or unsigned
	std::vector<char> bytes(4);
	// std::memcpy should be used instead
	// there is no any overflow here, but this 
	// approach won't work if one system is a little endian
	// and another is a big endian 
	memcpy(&bytes[0], (void*)&number, 4);

	// there are no any error checks here
	// catch (std::ios_base::failure& e) should be used
	// to caught errors (access denied error for example)
	std::ofstream file;
	file.open("data.dat", std::ios::binary | std::ios::out);
	// file.is_open() should be used to check
	// whether open succeeded
	file.write(&bytes[0], bytes.size());
	// if(file.bad()) should check for write errors
	// close should be called only if previous open succeeded
	file.close();

	return 0;
}
