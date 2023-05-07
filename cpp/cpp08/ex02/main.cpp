#include <string>
#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "MutantStack.hpp"

int main(void)
{
	std::srand(std::time(nullptr));
	MutantStack<int> mstack;
	mstack.push(5); //lifo
	mstack.push(17);
	std::cout << "top: " << mstack.top() << std::endl; //.top() returns a reference to the top element in the stack
	mstack.pop(); //removes the top element in the stack
	std::cout << "top: " << mstack.top() << std::endl;
	std::cout << "size: " << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);
	std::cout << "size: " << mstack.size() << std::endl;
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	std::cout << "MutantStack: ";
	while (it != ite)
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
	std::stack<int> s(mstack); //copy constructor
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "std::stack: ";
	while (!s.empty())
	{
		std::cout << s.top() << " ";
		s.pop();
	}
	std::cout << std::endl;
	return (0);
}