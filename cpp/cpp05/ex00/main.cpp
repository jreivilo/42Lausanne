#include "Bureaucrat.hpp"

int main()
{
	try
	{
		Bureaucrat b1("b1", 1);
		std::cout << b1.getGrade() << std::endl;
		b1.incrementGrade();
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl; //.what() is a method of the exception class
	}
	try
	{
		Bureaucrat b2("b2", 150);
		std::cout << b2.getGrade() << std::endl;
		b2.decrementGrade();
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << "----------------" << std::endl;
	{
		Bureaucrat b3("b3", 2);
		Bureaucrat b4 = b3;

		std::cout << b3.getName() << std::endl;
		std::cout << b4.getGrade() << std::endl;
		std::cout << b4.getName() << std::endl;
		std::cout << b3.getGrade() << std::endl;
	}
	std::cout << "----------------" << std::endl;
	{
		try 
		{
			Bureaucrat b5("AA", 0);
			std::cout << "COucou" << std::endl;
		}
		catch (std::exception & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return 0;
}
