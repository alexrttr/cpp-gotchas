#include "C.h"
#include "A.h"

#include <iostream>

C::C(std::shared_ptr<A>& classA) : _classA(classA)
{
}

void C::doSomething(int32_t value)
{
	if(_classA) _classA->doSomething2(value);
}

void C::doSomething2(int32_t value)
{
	std::cout << "In C " << value << std::endl;
}