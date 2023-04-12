#ifndef "DOG_HPP"
# define "DOG_HPP"

class Dog : public Animal
{
	public:
		Dog(); // default constructor
		Dog(Dog const & src); // copy constructor
		~Dog(); // destructor
		Dog & operator=(Dog const & rhs); // assignation operator

		void makeSound() const;
};