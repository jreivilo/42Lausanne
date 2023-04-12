#ifndef CAT_HPP
# define CAT_HPP

#include "Animal.hpp"

class Cat : public Animal
{
	public:
		Cat(); // default constructor
		Cat(Cat const & src); // copy constructor
		~Cat(); // destructor
		Cat & operator=(Cat const & rhs); // assignation operator

		void makeSound() const;
};