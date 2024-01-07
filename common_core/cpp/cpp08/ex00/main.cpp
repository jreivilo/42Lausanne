#include <string>
#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "easyfind.hpp"

int main(void)
{
	std::srand(std::time(nullptr));
	std::vector<int> v;
	for (int i = 0; i < 10; i++)
		v.push_back(std::rand() % 10);
	std::cout << "Vector: ";
	for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "easyfind(v, 5): " << *easyfind(v, 5) << std::endl;
	std::cout << "easyfind(v, 10): " << *easyfind(v, 10) << std::endl;
	return (0);
}

