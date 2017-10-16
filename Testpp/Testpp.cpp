#include <vector>
#include <iostream>
#include <memory>

class Kaas
{
	int x;
	int y;
	std::shared_ptr<int> p;

public:
	Kaas(int _x, int _y, int _z)
		: x{ _x }
		, y{ _y }
		, p{ std::make_shared<int>(_z) }
	{
		std::cout << "ctor" << std::endl;
	}

	/*Kaas(const Kaas &other) = delete;
	Kaas(Kaas&&) = delete;*/

	Kaas(const Kaas& other)
		: p{ other.p.get() }
		, x{ other.x }
		, y{ other.y }
	{
		std::cout << "I am copy" << std::endl;
		//x += 2; // <-- prevent inlineing
	}

	Kaas& operator=(const Kaas&) = delete;
	Kaas& operator=(Kaas&&) = delete;

	//Kaas(Kaas&& other) = delete;

	Kaas(Kaas&& other)
		: p{ other.p.get() }
		, x{ other.x }
		, y{ other.y }
	{
		other.p = nullptr;
		std::cout << "I am move" << std::endl;
		//x++; // <-- prevent inlineing
	}

	int GetX() { return x; }
};

class SomeClass
{
public:
	Kaas SomeFunc()
	{
		return { 17, 24, 86 };
	}
};

void testmove()
{
	SomeClass s;

	Kaas v(1, 2, 3);
	Kaas t(4, 5, 6);
	Kaas w(v);

	Kaas y(s.SomeFunc());
	std::cout << y.GetX() << std::endl;

	std::cout << w.GetX() << std::endl;
}

int main()
{
	std::string str;
	str.push_back('a');

	return 0;
}

