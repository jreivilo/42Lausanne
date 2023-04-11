#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>
#include <string>
#include <sstream>

class Animal
{
	protected:
		std::string type;
	public:
		Animal(); // default constructor
		Animal(Animal const & src); // copy constructor
		~Animal(); // destructor
		Animal & operator=(Animal const & rhs); // assignation operator

		std::string getType() const;
		virtual void makeSound() const;
};

#endif