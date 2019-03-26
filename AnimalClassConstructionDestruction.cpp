#include "pch.h" 
#include<iostream> 

class base {
public:
	base()
	{
		std::cout << "Constructing base \n";
	}

	virtual ~base()
	{
		std::cout << "Destructing base \n";
	}
};

class derived : public base {
public:
	derived()
	{
		std::cout << "Constructing derived \n";
	}

	~derived()
	{
		std::cout << "Destructing derived \n";
	}
};

int main(void)
{
	derived *d = new derived();
	base *b = d;
	delete b;
	getchar();

	return 0;
}