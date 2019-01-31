#include <iostream>
// this is C header without angle brekets
// it's a good idea to replace it with <cstring>
#include "string.h"

// argc and argv are not used and can be omitted
int main(int argc, char* argv[])
{
	// in C++ it's better to use std::string instead of regular buffer
	char input[255];
	// stack buffer overflow is possible here
	// user can input "no no no yes no" and space will be treated as end
	// of line so  std::istream::getline should be used instead
	// (for std::string std::getline should be used)
	// example:  std::cin.getline(input, 255);
 	std::cin >> input;
 	// std::strstr should be used instead (with cstring included)
	bool containsYes = strstr(input, "yes") != nullptr;
	// actual size of input is larger by one (includes null terminator)
    std::cout << "Size of input: " << strlen(input) << ", contains yes: " << (containsYes ? "true" : "false") << std::endl;
	return 0;
}
