#include <string>
#include <cstdint>
#include <iostream>


#include "Data.hpp"

uintptr_t serialize(Data* ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr)); // reinterpret_cast is used to convert a pointer into an integer
}

Data* deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data *>(raw)); // reinterpret_cast is used to convert an integer into a pointer
}

int main()
{
	Data *data = new Data;
	data->s1 = "Hello";
	data->n = 42;
	data->s2 = "World";

	std::cout << "data->s1: " << data->s1 << "\n";
	std::cout << "data->n: " << data->n << "\n";
	std::cout << "data->s2: " << data->s2 << "\n";

	uintptr_t raw = serialize(data);
	std::cout << "raw: " << raw << "\n";

	Data *data2 = deserialize(raw);
	std::cout << "data2->s1: " << data2->s1 << "\n";
	std::cout << "data2->n: " << data2->n << "\n";
	std::cout << "data2->s2: " << data2->s2 << "\n";

	delete data;
	return (0);
}

