#ifndef A_H_
#define A_H_

// these includes should be moved to cpp file
// as this header file doesn't use them
#include <iostream>
#include <string.h>
#include <malloc.h>

class A
{
private:
	char* _text = nullptr;
public:
	A();
	// as the class contains a pointer it should
	// manage the memory using copy constructor
	// and copy assignment operator
	A(A const& another);
	virtual ~A();

	void print(int32_t value);
};

#endif
