#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap()
{
	std::cout << "FragTrap default constructor called" << std::endl;
	name = "Default";
	hitPoints = 100;
	energyPoints = 100;
	attackDamage = 30;
	gateKeeperMode = false;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	std::cout << "FragTrap constructor called" << std::endl;
	this->name = name;
	hitPoints = 100;
	energyPoints = 100;
	attackDamage = 30;
	gateKeeperMode = false;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap Destructor called" << std::endl;
}

FragTrap::FragTrap(FragTrap const & src) : ClapTrap(src) //copy constructor
{
	std::cout << "FragTrap Copy constructor called" << std::endl;
	*this = src;
}

FragTrap & FragTrap::operator=(FragTrap const & rhs)
{
	std::cout << "FragTrap Assignation operator called" << std::endl;
	this->name = rhs.name;
	this->hitPoints = rhs.hitPoints;
	this->energyPoints = rhs.energyPoints;
	this->attackDamage = rhs.attackDamage;
	return *this;
}

//abilities
void FragTrap::attack(std::string const & target)
{
	if (this->energyPoints <=0)
	{
		std::cout << "FragTrap " << this->name  << "do not have enough energy." <<std::endl;
		return ;
	}
	std::cout << "FragTrap " << this->name << " attacks " << target << ", causing " << this->attackDamage << " points of damage!" << std::endl;
	this->energyPoints = this->energyPoints - 1;
}

void FragTrap::highFivesGuys()
{
	if (this->energyPoints <=0)
	{
		std::cout << "FragTrap " << this->name  << "do not have enough energy." <<std::endl;
		return ;
	}
	std::cout << "FragTrap " << this->name << " gives a high five to all the guys!" << std::endl;
}

