#ifndef AANIMAL_HPP
# define AANIMAL_HPP

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
		virtual ~Animal(); // destructor
		Animal & operator=(Animal const & rhs); // assignation operator

		std::string getType() const;
		virtual void makeSound() const = 0;
};


// The equal sign followed by zero is used to signify that this is a pure virtual function. 
// This means that the function has no implementation, and must be implemented by any class that inherits from the class containing the pure virtual function. 
// It is used to signify that the class containing the pure virtual function is an abstract class, and cannot be instantiated.

#endif