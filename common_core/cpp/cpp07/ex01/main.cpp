#include <string>
#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "iter.hpp"

template <typename T>

void print(T const &x)
{
	std::cout << x << std::endl;
}

int main( void ) 
{
	int a[5] = {0, 1, 2, 3, 4};
	iter(a, 5, print);
	return 0;
}

