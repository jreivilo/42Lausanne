#include "ScavTrap.hpp"

ScavTrap::ScavTrap()
{
	std::cout << "ScavTrap default constructor called" << std::endl;
	this->name = "Default";
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->attackDamage = 20;
	this->gateKeeperMode = false;
}

ScavTrap::ScavTrap(std::string name)
{
	std::cout << "ScavTrap constructor called" << std::endl;
	this->name = name;
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->attackDamage = 20;
	this->gateKeeperMode = false;
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap Destructor called" << std::endl;
}

ScavTrap::ScavTrap(ScavTrap const & src) : ClapTrap(src) //copy constructor
{
	std::cout << "ScavTrap Copy constructor called" << std::endl;
	*this = src;
}
// ClapTrap(src) initializes the base class of ScavTrap, which is ClapTrap. 
//This allows the copy constructor to access the members of ClapTrap, so they can be copied to the new ScavTrap.

ScavTrap & ScavTrap::operator=(ScavTrap const & rhs)
{
	std::cout << "ScavTrap Assignation operator called" << std::endl;
	this->name = rhs.name;
	this->hitPoints = rhs.hitPoints;
	this->energyPoints = rhs.energyPoints;
	this->attackDamage = rhs.attackDamage;
	return *this;
}


//abilities
void ScavTrap::attack(std::string const & target)
{
	if (this->energyPoints <=0)
	{
		std::cout << "ScavTrap " << this->name  << "do not have enough energy." <<std::endl;
		return ;
	}
	std::cout << "ScavTrap " << this->name << " attacks " << target << ", causing " << this->attackDamage << " points of damage!" << std::endl;
	this->energyPoints = this->energyPoints - 1;
}

void ScavTrap::guardGate()
{
	if (this->gateKeeperMode == true)
	{
		std::cout << "ScavTrap " << this->name << " is already in Gate keeper mode" << std::endl;
		return ;
	}
	std::cout << "ScavTrap " << this->name << " have enterred in Gate keeper mode" << std::endl;
	this->gateKeeperMode = true;
}

