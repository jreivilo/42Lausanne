#ifndef DATA_HPP
# define DATA_HPP

# include <iostream>
# include <string>
# include <cstdint>

typedef struct Data
{
	std::string s1;
	int n;
	std::string s2;
} Data;

uintptr_t serialize(Data* ptr);
Data* deserialize(uintptr_t raw);

#endif