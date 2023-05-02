#include <string>
#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <ctime>


#include "Base.hpp"


Base *generate(void)
{
	int random = rand() % 3;
	if (random == 0)
		return (new A);
	else if (random == 1)
		return (new B);
	else
		return (new C);
}

void identify_from_pointer(Base *p) // p is a pointer to a Base class
{
	if (dynamic_cast<A *>(p)) // dynamic_cast returns a pointer to the casted class if the cast succeeds, otherwise it returns NULL
		std::out << "A\n";
	else if (dynamic_cast<B *>(p))
		std::cout << "B\n";
	else if (dynamic_cast<C *>(p))
		std::cout << "C\n";
}

void identify_from_reference(Base &p) // p is a reference to a Base class
{
	try
	{
		A &a = dynamic_cast<A &>(p); // dynamic_cast throws an exception if the cast fails
		std::cout << "A\n";
		(void)a;
	}
	catch (std::exception &e) {}
	try
	{
		B &b = dynamic_cast<B &>(p);
		std::cout << "B\n";
		(void)b;
	}
	catch (std::exception &e) {}
	try
	{
		C &c = dynamic_cast<C &>(p);
		std::cout << "C\n";
		(void)c;
	}
	catch (std::exception &e) {}
}

int main(void)
{
	srand(time(NULL)); // Seed random number generator
	Base *base = generate();
	identify_from_pointer(base);
	identify_from_reference(*base);
	delete base;
	return (0);
}

