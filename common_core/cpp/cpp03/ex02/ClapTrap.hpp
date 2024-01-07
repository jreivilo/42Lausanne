#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>
#include <string>


class ClapTrap
{
	protected:
		std::string		name;
		int				hitPoints;
		int				energyPoints;
		int				attackDamage;
	public:
		ClapTrap();
		ClapTrap(std::string name);
		~ClapTrap();

		ClapTrap(ClapTrap const & src ); //copy constructor
		ClapTrap & operator=( ClapTrap const & rhs ); //assignment operator overload (assignation operator) //rhs = right hand side

		void attack(std::string const & target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
};

#endif