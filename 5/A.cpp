#include "A.h"
#include "B.h"

#include <iostream>

A::A(std::shared_ptr<B>& classB) : _classB(classB)
{
}

void A::doSomething(int32_t value)
{
	if(_classB) _classB->doSomething2(value);
}

void A::doSomething2(int32_t value)
{
	std::cout << "In A " << value << std::endl;
}