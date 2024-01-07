#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

# include <iostream>

class WrongAnimal
{
	protected:
		std::string type;
	public:
		WrongAnimal();
		WrongAnimal(WrongAnimal const & src);
		~WrongAnimal();
		WrongAnimal & operator=(WrongAnimal const & rhs);

		std::string getType() const;
		void makeSound() const;
};

#endif