#include <iostream>

class Logger
{
private:
	static void logs()
	{

		std::cerr << std::endl;
	}
	template <class A, class ...B> static void logs(A argHead, B... argTail) {
		std::cerr << argHead << " ";
		logs(argTail...);
	}
public:
	template <class B,class ...A> static void log(B te,A... argHead) {
		std::cerr << te <<": ";
		logs(argHead...);
	}
};

