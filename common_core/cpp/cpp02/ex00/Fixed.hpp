#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <string>


class Fixed
{
	private:
		int					_rawBits;
		static const int	_fractionalBits = 8;
	public:
		Fixed();
		~Fixed();
		Fixed( Fixed const & src ); //copy constructor
		Fixed & operator=( Fixed const & rhs ); //assignment operator overload (assignation operator) //rhs = right hand side
		int		getRawBits( void ) const;
		void	setRawBits( int const raw );
};


//whats of a copy constructor?
//copy constructor is a constructor that creates an object by initializing it with an object of the same class, which has been created previously. The copy constructor is used to:
//initialize one object from another of the same type

//explain assignment operator
//The assignment operator is used to copy the value of one object to another already initialized object of the same type. It is a member function which is called when the = operator is used with the object as left operand.

#endif