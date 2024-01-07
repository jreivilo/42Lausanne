#include "RPN.hpp"

RPN::RPN()
{
	// std::cout << "Default constructor called" << std::endl;
}

RPN::RPN(std::string expression)
{
	// std::cout << "Parametric constructor called" << std::endl;
	std::string token;
	std::istringstream iss(expression);
	while (std::getline(iss, token, ' '))
	{
		//check token validity
		if (token.length() > 1)
			throw InvalidTokenException();
		else if (token.length() == 1 && !std::isdigit(token[0]) && token[0] != '+' && token[0] != '-' && token[0] != '*' && token[0] != '/')
			throw InvalidTokenException();
		if (token == "+")
			this->add();
		else if (token == "-")
			this->subtract();
		else if (token == "*")
			this->multiply();
		else if (token == "/")
			this->divide();
		else
			this->stack.push_back(std::stoi(token));
	}
}

RPN::~RPN()
{
	// std::cout << "Destructor called" << std::endl;
}

RPN::RPN( RPN const & src )
{
	// std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

RPN & RPN::operator=( RPN const & rhs )
{
	// std::cout << "Assignation operator called" << std::endl;
	if (this != &rhs) // check for self-assignment
		this->stack = rhs.stack; // copy the value
	return *this; // return the existing object so we can chain this operator
}

void RPN::add()
{
	if (this->stack.size() < 2)
		throw NotEnoughValuesException();
	int a = this->stack.back();
	this->stack.pop_back();
	int b = this->stack.back();
	this->stack.pop_back();
	this->stack.push_back(a + b);
}

void RPN::subtract()
{
	if (this->stack.size() < 2)
		throw NotEnoughValuesException();
	int a = this->stack.back();
	this->stack.pop_back();
	int b = this->stack.back();
	this->stack.pop_back();
	this->stack.push_back(b - a);
}

void RPN::multiply()
{
	if (this->stack.size() < 2)
		throw NotEnoughValuesException();
	int a = this->stack.back();
	this->stack.pop_back();
	int b = this->stack.back();
	this->stack.pop_back();
	this->stack.push_back(a * b);
}

void RPN::divide()
{
	if (this->stack.size() < 2)
		throw NotEnoughValuesException();
	int a = this->stack.back();
	this->stack.pop_back();
	int b = this->stack.back();
	this->stack.pop_back();
	if (a == 0)
		throw DivisionByZeroException();
	this->stack.push_back(b / a);
}

int RPN::getNumber()
{
	if (stack.empty())
		throw EmptyStackException();
	if (stack.size() != 1)
		throw MoreThanOneNumberException();
	int n = stack.back();
	stack.pop_back();
	return (n);
}

const char* RPN::EmptyStackException::what() const throw()
{
	return ("Stack is empty");
}

const char* RPN::NotEnoughValuesException::what() const throw()
{
	return ("Not enough values in stack");
}

const char* RPN::DivisionByZeroException::what() const throw()
{
	return ("Division by zero");
}

const char* RPN::MoreThanOneNumberException::what() const throw()
{
	return ("More than one number in stack");
}

const char* RPN::InvalidTokenException::what() const throw()
{
	return ("Invalid token");
}
