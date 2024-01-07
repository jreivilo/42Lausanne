#include "error.hpp"

Error::Error()
{
}

Error::Error(const Error &src)
{
	*this = src;
}

Error::~Error()
{
}

Error &Error::operator=(const Error &src)
{
	(void)src;
	return (*this);
}

const char *Error::WrongNumberOfArguments::what() const throw()
{
	return ("Wrong number of arguments");
}

const char *Error::WrongFormat::what() const throw()
{
	return ("Wrong format");
}

const char *Error::Overflow_underflow::what() const throw()
{
	return ("Overflow or underflow");
}