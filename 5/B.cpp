#include "B.h"
#include "C.h"

#include <iostream>

B::B()
{
}

void B::doSomething(int32_t value)
{
	if(classC) classC->doSomething2(value);
}

void B::doSomething2(int32_t value)
{
	std::cout << "In B " << value << std::endl;
}
