#include "A.h"

void execute(A classA, int32_t value)
{
	classA.print(value);
	// explicit desutructor will be called right 
	// after classA copy goes out of scope
	// and memory will be free
}

int main(int argc, char* argv[])
{
	A classA;
	// default copy constructor will make a shallow
	// copy of the A instance so all pointers inside
	// will point to the same memory region
	// later the desctructor will free it 
	// several times
	execute(classA, 5);
	execute(classA, 12);
	return 0;
}
