#include <string>
#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Array.hpp"

int		main(void)
{
	Array<int>		intArray(5);
	Array<float>	floatArray(5);
	Array<double>	doubleArray(5);
	Array<char>		charArray(5);
	Array<std::string>	stringArray(5);

	std::srand(std::time(NULL));
	for (int i = 0; i < 5; i++)
	{
		intArray[i] = std::rand() % 100;
		floatArray[i] = static_cast<float>(std::rand() % 100);
		doubleArray[i] = static_cast<double>(std::rand() % 100);
		charArray[i] = static_cast<char>(std::rand() % 26 + 65);
		stringArray[i] = "Hello";
	}

	Array<int>		intArray2(intArray);

	std::cout << "intArray: ";
	for (int i = 0; i < 5; i++)
		std::cout << intArray[i] << " ";
	std::cout << std::endl;

	std::cout << "intArray2: ";
	for (int i = 0; i < 5; i++)
		std::cout << intArray2[i] << " ";
	std::cout << std::endl;

	std::cout << "floatArray: ";
	for (int i = 0; i < 5; i++)
		std::cout << floatArray[i] << " ";
	std::cout << std::endl;

	std::cout << "doubleArray: ";
	for (int i = 0; i < 5; i++)
		std::cout << doubleArray[i] << " ";
	std::cout << std::endl;

	std::cout << "charArray: ";
	for (int i = 0; i < 5; i++)
		std::cout << charArray[i] << " ";
	std::cout << std::endl;

	std::cout << "stringArray: ";
	for (int i = 0; i < 5; i++)
		std::cout << stringArray[i] << " ";
	std::cout << std::endl;

	try
	{
		std::cout << "intArray[5]: " << intArray[5] << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << "intArray[5]: " << e.what() << std::endl;
	}

	try
	{
		std::cout << "floatArray[5]: " << floatArray[5] << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << "floatArray[5]: " << e.what() << std::endl;
	}
}

