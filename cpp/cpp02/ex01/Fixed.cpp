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
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &rhs) // check for self-assignment
		this->_rawBits = rhs.getRawBits();
	return *this;
	//We return a pointer in order to enable the use of the assignment operator,
	// allowing us to assign one object to another. 
	// This is done by returning a pointer to the current object, 
	// which allows us to use the assignment operator to assign 
	// the right-hand side object to the current object.
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
	return ((float)this->_rawBits / (1 << this->_fractionalBits)); // / is a bitwise operator that shifts the bits of the number to the left and fills the voids left as a result of the shifting with 0s.
}

int Fixed::toInt( void ) const
{
	return (this->_rawBits >> this->_fractionalBits); // >> is a bitwise operator that shifts the bits of the number to the right and fills the voids left as a result of the shifting with 0s.
}



std::ostream & operator<<( std::ostream & o, Fixed const & rhs )
{
	o << rhs.toFloat(); // << is a bitwise operator that shifts the bits of the number to the left and fills the voids left as a result of the shifting with 0s.
	return o;
}




//explain polymorphism in C++ and how it is used in the context of classes and inheritance
// polymorphism is the ability of an object to take on many forms. The most common use of polymorphism in OOP occurs when a parent class reference is used to refer to a child class object.
// 