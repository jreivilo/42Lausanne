#ifndef DOG_HPP
# define DOG_HPP

#include "AAnimal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
	private:
		Brain *brain;
	public:
		Dog(); // default constructor
		Dog(Dog const & src); // copy constructor
		~Dog(); // destructor
		Dog & operator=(Dog const & rhs); // assignation operator

		void makeSound() const;
};

#endif

