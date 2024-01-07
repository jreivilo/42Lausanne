#include <string>
#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Span.hpp"

int main(void)
{
	std::srand(std::time(nullptr));
	Span sp = Span(5); // create Span object with size 5
	sp.addNumber(5);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << "shortestSpan: " << sp.shortestSpan() << std::endl;
	std::cout << "longestSpan: " << sp.longestSpan() << std::endl;

	std::cout << "----------------------------------------" << std::endl;

	Span sp2 = Span(10000);
	std::vector<int> orignal;
	for (int i = 0; i < 10000; i++)
		orignal.push_back(std::rand() % 225);
	sp2.addNumber(orignal.begin(), orignal.end());
	try
	{
		sp2.addNumber(orignal.begin(), orignal.end());
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	std::cout << "shortestSpan: " << sp2.longestSpan() << std::endl;

	std::cout << "----------------------------------------" << std::endl;

	try
	{
		sp.addNumber(22);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}

