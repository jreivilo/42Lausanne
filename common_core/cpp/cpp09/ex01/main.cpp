#include <string>
#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "RPN.hpp"

int main(int argc, char ** argv)
{
	if (argc == 2)
	{
		try
		{
			RPN rpn(argv[1]);
			std::cout << "Result: ";
			std::cout << rpn.getNumber() << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}

	}
	else
		std::cout << "Usage: ./rpn \"<expression>\"" << std::endl;
	return (0);
}

