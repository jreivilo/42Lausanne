#include "error.hpp"

#include <iostream>
#include <string>
#include <limits.h>
#include <iomanip>      // std::setprecision

#include <iostream>
#include <iomanip>
#include <sstream>
#include <float.h>

int set_precision(float n_float, double n_double)
{
	std::string str_float;
	std::string str_double;

	str_float = std::to_string(n_float);
	str_double = std::to_string(n_double);

	int i = 0;
	int precision = 0;
	int precision_float = 0;
	int precision_double = 0;

	while (str_float[i])
		i++;
	i--;
	while (str_float[i] == '0')
		i--;
	while (str_float[i] != '.')
	{
		precision_float++;
		i--;
	}

	i = 0;
	while (str_double[i])
		i++;
	i--;
	while (str_double[i] == '0')
		i--;
	while (str_double[i] != '.')
	{
		precision_double++;
		i--;
	}
	if (precision_float > precision_double)
		precision = precision_float;
	else
		precision = precision_double;
	//print precision
	std::cout << "precision: " << precision << "\n";
	return (precision);
}

void	display(int n_char, double n_int, double n_float, double n_double)
{
	// int precision = set_precision(n_float, n_double);
	int precision = 1;

	std::cout << "char: ";
	if (n_char >= 32 && n_char <= 126)
		std::cout << "'" << static_cast<char>(n_char) << "'\n";	// static_cast<char>(n_char) is the same as (char)n_char
	else if ((n_char >= 0 && n_char <= 31) || n_char == 127) //127 is the DEL character
		std::cout << "Non displayable\n";
	else
		std::cout << "impossible\n";

	std::cout << "int: ";
	if (n_int >= INT_MIN && n_int <= INT_MAX)
		std::cout <<static_cast<int>(n_int) << "\n";
	else
		std::cout << "impossible\n";
	
	if (n_float >= FLT_MIN && n_float <= FLT_MAX)
		std::cout << "float: " << std::fixed << std::setprecision(precision) << static_cast<float>(n_float) << "f\n";
	else
		std::cout << "float: impossible\n";

	if (n_double >= DBL_MIN && n_double <= DBL_MAX)
		std::cout << "double: " << std::fixed << std::setprecision(precision) << static_cast<double>(n_double) << "\n";
	else
		std::cout << "double: impossible\n";
}

bool	check_float(std::string str)
{
	int i = 0;
	int dot = 0;
	int sign = 0;
	int e = 0;
	int num = 0;
	int other = 0;

	if (str[i] == '+' || str[i] == '-')
		sign++;
	while (str[i])
	{
		if (str[i] == '.')
			dot++;
		if (str[i] == 'e')
			e++;
		if (str[i] >= '0' && str[i] <= '9')
			num++;
		if (str[i] != '.' && str[i] != 'e' && str[i] != '+' && str[i] != '-' && (str[i] < '0' || str[i] > '9'))
			other++;
		i++;
	}
	// std::cout << "other: " << other << "\n";
	if (str[i - 1] != 'f')
		return (false);
	if (dot > 1 || sign > 1 || e > 1 || num == 0 || other != 1)
		return (false);
	return (true);
}

bool check_double(std::string str)
{
	int i = 0;
	int dot = 0;
	int sign = 0;
	int e = 0;
	int num = 0;

	if (str[i] == '+' || str[i] == '-')
		sign++;
	while (str[i])
	{
		if (str[i] == '.')
			dot++;
		if (str[i] == 'e')
			e++;
		if (str[i] >= '0' && str[i] <= '9')
			num++;
		i++;
	}
	if (dot > 1 || sign > 1 || e > 1 || num == 0)
		return (false);
	return (true);
}

bool check_int(std::string str)
{
	int i = 0;
	int sign = 0;
	int num = 0;

	if (str[i] == '+' || str[i] == '-')
	{
		sign++;
		i++;
	}
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		i++;
		num++;
	}
	if (sign > 1 || num == 0)
		return (false);
	return (true);
}

void float_transpose(std::string str)
{
	std::cout << "float_transpose\n";
	if (check_float(str) == false)
		throw Error::WrongFormat();
	str.pop_back();
	double n_double = std::stod(str);
	// int n_int = static_cast<int>(n_double);
	int n_char = static_cast<int>(n_double);
	display(n_char, n_double, n_double, n_double);
}

void double_transpose(std::string str)
{
	std::cout << "double transpose\n";
	if (check_double(str) == false)
		throw Error::WrongFormat();
	double n_double = std::stod(str);
	// float n_float = static_cast<float>(n_double);
	// int n_int = static_cast<int>(n_double);
	int n_char = static_cast<int>(n_double);
	display(n_char, n_double, n_double, n_double); 
}

void	int_transpose(std::string str)
{
	std::cout << "int transpose\n";
	if (check_int(str) == false)
		throw Error::WrongFormat();
	double n_double = std::stod(str);
	// float n_float = static_cast<float>(n_double);
	int n_char = static_cast<int>(n_double);
	display(n_char, n_double, n_double, n_double);
}

void	char_transpose(std::string str)
{
	
	if (str.length() != 1)
		throw Error::WrongFormat();
	char c = str[0];
	display(static_cast<int>(c), static_cast<int>(c), static_cast<float>(c), static_cast<double>(c));
}

bool is_special_case(std::string str)
{
	if (str == "nan" || str == "nanf" || str == "inf" || str == "inff" || str == "+inf" || str == "+inff" || str == "-inf" || str == "-inff")
		return (true);
	return (false);
}

void special_case(std::string str)
{
	if (str == "nan" || str == "nanf")
		std::cout << "char: impossible\nint: impossible\nfloat: nanf\ndouble: nan\n";
	if (str == "inf" || str == "inff" || str == "+inf" || str == "+inff")
		std::cout << "char: impossible\nint: impossible\nfloat: inf\ndouble: inf\n";
	if (str == "-inf" || str == "-inff")
		std::cout << "char: impossible\nint: impossible\nfloat: -inf\ndouble: -inf\n";
}


int main(int argc, char **argv)
{
	try
	{
		if (argc != 2)
			throw Error::WrongNumberOfArguments();
		if (is_special_case(argv[1]) == true)
		{
			special_case(argv[1]);
			return (0);
		}
		std::string str(argv[1]);
		if (str.back() == 'f') //.back returns a reference to the last character in the string
			float_transpose(str);
		else if (str.find('.') != std::string::npos) //npos is a static member constant value with the greatest possible value for an element of type size_t.
			double_transpose(str);
		else if (str[0] == '+' || str[0] == '-' || (str[0] >= '0' && str[0] <= '9'))
			int_transpose(str);
		else
			char_transpose(str);
		// if (str.find('.') != std::string::npos) //npos is a static member constant value with the greatest possible value for an element of type size_t.
		// 	double_transpose(str);


	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}