#ifndef A_H_
#define A_H_

#include <memory>
class B;

class A
{
private:
	std::shared_ptr<B> _classB;
public:
	// constructor should be explicit
	explicit A(std::shared_ptr<B>& classB);
	virtual ~A() {}

	void doSomething(int32_t value);
	void doSomething2(int32_t value);
};

#endif
