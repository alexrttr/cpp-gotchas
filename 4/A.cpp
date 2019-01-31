#include "A.h"
#include <iostream>

A::A()
{
	// M_CHECK_ACTION should be set to 3 to enforce
	// quit on memory manipulations similar to double free
	mallopt(M_CHECK_ACTION, 0);
	_text = new char[100];
	strcpy(_text, "Hello world!");
}

// deep copy example:
A::A(A const& original)
{
	try
	{
		_text = new char[100];
	}
	catch(std::bad_alloc&) 
	{
		// copy failed
		// error handler
		return;
	}		
	
	char *originalText = original.getText().c_str();
	
	if (strlen(originalText) > 0)
	{
		_text[0] = '\0';
		// using strncat as it checks for the size
		// strcpy with custom check can be used as well
		std::strncat(_text, originalText, sizeof(_text) - 1);
	}
}

A::~A()
{
	// memory leak here
	// delete[] text should be used instead
	delete[] _text;
}

void A::print(int32_t value)
{
	if(value < 10) std::cout << _text << ' ' << value << std::endl;
	else std::cerr << "Too large value..." << std::endl;
}
