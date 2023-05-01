#ifndef ERROR_HPP
#define ERROR_HPP

#include <exception>
#include <iostream>
#include <string>

class Error
{
public:
	Error();
	Error(const Error &src);
	~Error();

	Error &operator=(const Error &src);

	class WrongNumberOfArguments : public std::exception
	{
		public:
			virtual const char *what() const throw();
	};

	class WrongFormat : public std::exception
	{
		public:
			virtual const char *what() const throw();
	};

	class Overflow_underflow : public std::exception
	{
		public:
			virtual const char *what() const throw();
	};
};

#endif