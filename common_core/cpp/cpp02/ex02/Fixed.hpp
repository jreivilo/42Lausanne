#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <string>
#include <cmath>


class Fixed
{
	private:
		int					_rawBits;
		static const int	_fractionalBits = 8;
	public:
		Fixed();
		~Fixed();

		Fixed(Fixed const & src ); //copy constructor
		Fixed(int const raw ); //copy constructor convert int to fixed
		Fixed(float const raw ); //copy constructor convert float to fixed

		Fixed & operator=( Fixed const & rhs ); //assignment operator overload (assignation operator) //rhs = right hand side

		bool operator>( Fixed const & rhs ) const; //The first const ensures that the object on which the operator is called is not changed by the operator. 
		//The second const ensures that the object passed as an argument to the operator is also not changed by the operator.
		bool operator<( Fixed const & rhs ) const;
		bool operator>=( Fixed const & rhs ) const;
		bool operator<=( Fixed const & rhs ) const;
		bool operator==( Fixed const & rhs ) const;
		bool operator!=( Fixed const & rhs ) const;

		Fixed operator+( Fixed const & rhs ) const;
		Fixed operator-( Fixed const & rhs ) const;
		Fixed operator*( Fixed const & rhs ) const;
		Fixed operator/( Fixed const & rhs ) const;

		Fixed & operator++( void ); //prefix
		Fixed operator++( int ); //postfix
		Fixed & operator--( void ); //prefix
		Fixed operator--( int ); //postfix

		// The difference between the two is that the prefix version of the operator returns a reference to the object itself, 
		// while the postfix version returns a copy of the object before it was modified. 
		// This allows the prefix version to be used in an expression, 
		// while the postfix version can be used to store the original value of the object before it is modified.



		int		getRawBits( void ) const;
		void	setRawBits( int const raw );

		float	toFloat( void ) const;
		int		toInt( void ) const;
	
		static Fixed & min( Fixed & a, Fixed & b );
		static Fixed const & min( Fixed const & a, Fixed const & b );
		static Fixed & max( Fixed & a, Fixed & b );
		static Fixed const & max( Fixed const & a, Fixed const & b );
};

std::ostream & operator<<( std::ostream & o, Fixed const & rhs ); //overload the << operator

//whats of a copy constructor?
//copy constructor is a constructor that creates an object by initializing it with an object of the same class, which has been created previously. The copy constructor is used to:
//initialize one object from another of the same type

//explain assignment operator
//The assignment operator is used to copy the value of one object to another already initialized object of the same type. It is a member function which is called when the = operator is used with the object as left operand.

#endif