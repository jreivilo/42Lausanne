#include "Fixed.hpp"

Fixed::Fixed()
{
	// std::cout << "Default constructor called" << std::endl;
	this->_rawBits = 0;
}

Fixed::~Fixed()
{
	// std::cout << "Destructor called" << std::endl;
}



Fixed::Fixed( Fixed const & src )
{
	// std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

Fixed::Fixed( int const raw )
{
	// std::cout << "Int constructor called" << std::endl;
	this->_rawBits = raw << this->_fractionalBits;
}

Fixed::Fixed( float const raw )
{
	// std::cout << "Float constructor called" << std::endl;
	this->_rawBits = roundf(raw * (1 << this->_fractionalBits));
}

Fixed & Fixed::operator=( Fixed const & rhs )
{
	// std::cout << "Assignation operator called" << std::endl;
	if (this != &rhs) // check for self-assignment
		this->_rawBits = rhs.getRawBits(); // copy the value
	return *this; // return the existing object so we can chain this operator
}



bool Fixed::operator>( Fixed const & rhs ) const
{
	return (this->_rawBits > rhs.getRawBits()); 
}

bool Fixed::operator<( Fixed const & rhs ) const
{
	return (this->_rawBits < rhs.getRawBits());
}

bool Fixed::operator>=( Fixed const & rhs ) const 
{
	return (this->_rawBits >= rhs.getRawBits());
}

bool Fixed::operator<=( Fixed const & rhs ) const
{
	return (this->_rawBits <= rhs.getRawBits());
}

bool Fixed::operator==( Fixed const & rhs ) const
{
	return (this->_rawBits == rhs.getRawBits());
}

bool Fixed::operator!=( Fixed const & rhs ) const
{
	return (this->_rawBits != rhs.getRawBits());
}



Fixed Fixed::operator+( Fixed const & rhs ) const
{
	return (Fixed(this->toFloat() + rhs.toFloat()));
}

Fixed Fixed::operator-( Fixed const & rhs ) const
{
	return (Fixed(this->toFloat() - rhs.toFloat()));
}

Fixed Fixed::operator*( Fixed const & rhs ) const
{
	return (Fixed(this->toFloat() * rhs.toFloat()));
}

Fixed Fixed::operator/( Fixed const & rhs ) const
{
	return (Fixed(this->toFloat() / rhs.toFloat()));
}



Fixed & Fixed::operator++( void )
{
	this->_rawBits++;
	return (*this);
}

Fixed Fixed::operator++( int )
{
	Fixed tmp(*this); // copy the current object
	this->_rawBits++;
	return (tmp); // return the copy
}

Fixed & Fixed::operator--( void )
{
	this->_rawBits--;
	return (*this);
}

Fixed Fixed::operator--( int )
{
	Fixed tmp(*this);
	this->_rawBits--;
	return (tmp);
}



int Fixed::getRawBits( void ) const
{
	// std::cout << "getRawBits member function called" << std::endl;
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



Fixed & Fixed::min( Fixed & a, Fixed & b )
{
	return (a < b ? a : b);
}

Fixed const & Fixed::min( Fixed const & a, Fixed const & b )
{
	return (a < b ? a : b);
}

Fixed & Fixed::max( Fixed & a, Fixed & b )
{
	return (a > b ? a : b);
}

Fixed const & Fixed::max( Fixed const & a, Fixed const & b )
{
	return (a > b ? a : b);
}


std::ostream & operator<<( std::ostream & o, Fixed const & rhs ) 
{
	o << rhs.toFloat(); //
	return o; //
}




//explain polymorphism in C++ and how it is used in the context of classes and inheritance
// polymorphism is the ability of an object to take on many forms. The most common use of polymorphism in OOP occurs when a parent class reference is used to refer to a child class object.
// 