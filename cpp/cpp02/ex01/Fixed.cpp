#include "Fixed.hpp"

Fixed::Fixed()
{
	std::cout << "Default constructor called" << std::endl;
	this->_rawBits = 0;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed( Fixed const & src )
{
	std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

Fixed::Fixed( int const raw )
{
	std::cout << "Int constructor called" << std::endl;
	this->_rawBits = raw << this->_fractionalBits;
}

Fixed::Fixed( float const raw )
{
	std::cout << "Float constructor called" << std::endl;
	this->_rawBits = roundf(raw * (1 << this->_fractionalBits));
}

Fixed & Fixed::operator=( Fixed const & rhs )
{
	std::cout << "Assignation operator called" << std::endl;
	this->_rawBits = rhs.getRawBits(); //getRawBits is a const function so it can be called on a const object
	return *this; //return the object that called the function
}

int Fixed::getRawBits( void ) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (this->_rawBits);
}

void Fixed::setRawBits( int const raw )
{
	this->_rawBits = raw;
}

float Fixed::toFloat( void ) const
{
	return ((float)this->_rawBits / (1 << this->_fractionalBits));
}

int Fixed::toInt( void ) const
{
	return (this->_rawBits >> this->_fractionalBits);
}





//explain polymorphism in C++ and how it is used in the context of classes and inheritance
// polymorphism is the ability of an object to take on many forms. The most common use of polymorphism in OOP occurs when a parent class reference is used to refer to a child class object.
// 