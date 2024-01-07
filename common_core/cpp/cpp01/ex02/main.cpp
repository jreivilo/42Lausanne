#include <iostream>
#include <string>

int	main()
{
	std::string string = "HI THIS IS BRAIN";
	std::string *stringPTR = &string;
	std::string &stringREF = string;

	std::cout << "adress of string: " << &string << std::endl;
	std::cout << "adress of stringPTR: " << stringPTR << std::endl;
	std::cout << "adress of stringREF: " << &stringREF << std::endl;

	std::cout << "stringPTR: " << *stringPTR << std::endl;
	std::cout << "stringREF: " << stringREF << std::endl;
}