

//#define LOG(...) Logger::log(__VA_ARGS__)
#include<iostream>

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
template <class File,class A,class ...B> static void  log(File file,A note,B... argHead) {
	std::cerr << note <<": ";
	logs(argHead...);
}

};

