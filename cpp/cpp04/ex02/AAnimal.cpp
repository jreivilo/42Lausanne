#include "AAnimal.hpp"

Animal::Animal() : type("Animal")
{
	std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(Animal const & src)
{
	std::cout << "Animal copy constructor called" << std::endl;
	*this = src;
}

Animal::~Animal()
{
	std::cout << "Animal destructor called" << std::endl;
}

Animal & Animal::operator=(Animal const & rhs)
{
	std::cout << "Animal assignation operator called" << std::endl;
	if (this != &rhs)
		this->type = rhs.type;
	return *this;
}

std::string Animal::getType() const
{
	return this->type;
}

// void Animal::makeSound() const
// {
// 	std::cout << "Animal sound" << std::endl;
// }

// No, you should not define the function in the abstract class. 
// The point of a pure virtual function is that it is not implemented in the abstract class, but must be implemented by any class that inherits from it.