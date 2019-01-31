#ifndef C_H_
#define C_H_

#include <memory>
class A;

class C
{
private:
	std::shared_ptr<A> _classA;
public:
	// explicit is missing
	explicit C(std::shared_ptr<A>& classA);
	virtual ~C() {}

	void doSomething(int32_t value);
	void doSomething2(int32_t value);
};

#endif
