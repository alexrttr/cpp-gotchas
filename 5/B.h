#ifndef B_H_
#define B_H_

#include <memory>
class C;

class B
{
public:
	std::shared_ptr<C> classC;

	B();
	virtual ~B() {}

	void doSomething(int32_t value);
	void doSomething2(int32_t value);
};

#endif
