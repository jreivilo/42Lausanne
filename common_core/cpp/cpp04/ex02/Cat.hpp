#ifndef CAT_HPP
# define CAT_HPP

#include "AAnimal.hpp"
#include "Brain.hpp"

class Cat : public Animal 
{
	private:
		Brain *brain;
	public:
		Cat(); // default constructor
		Cat(Cat const & src); // copy constructor
		~Cat(); // destructor
		Cat & operator=(Cat const & rhs); // assignation operator

		void makeSound() const;
};

#endif

