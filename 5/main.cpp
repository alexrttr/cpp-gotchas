// it's a good idea to apply such includes order:
// curent .h
// C system headers
// C++ system headers
// Other libraries' .h files
// Project's .h files

#include "A.h"
#include "B.h"
#include "C.h"
#include <iostream>
#include <chrono>
#include <thread>

int main(int argc, char* argv[])
{
	for(int32_t i = 0; i < 10; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::shared_ptr<B> classB(new B());
		std::shared_ptr<A> classA(new A(classB));
		std::shared_ptr<C> classC(new C(classA));
		
		// there is a cyclic reference here
		// classA share ownership of classB instance with current scope
		// classC share ownership of classA instance (including its private classB instance)
		// classB instance is going to own classC instance with its private classA instance
		// which includes its private classB instance
		// it can be resolved by using weak pointer (however redesign 
		// could be even better)
		classB->classC = classC;
		classA->doSomething(i);
		classB->doSomething(i);
		classC->doSomething(i);
	}
	return 0;	
}
