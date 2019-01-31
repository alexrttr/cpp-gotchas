#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>

// main1 and main2 are executed on different computers.

int main(int argc, char* argv[])
{
	// the size of the pointer shouldn't be hardcoded
	std::vector<char> bytes(4);
	std::ifstream file;
	// there is no error handling here
	file.open("data.dat", std::ios::binary | std::ios::in);
	file.read(&bytes[0], 4);
	file.close();

	int32_t number = 0;
	memcpy((void*)&number, &bytes[0], 4);

	std::cout << "Number is: " << number << std::endl;
	return 0;
}
