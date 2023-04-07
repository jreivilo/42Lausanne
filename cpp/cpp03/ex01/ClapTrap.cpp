#include "ClapTrap.hpp"


ClapTrap::ClapTrap()
{
	std::cout << "ClapTrap default constructor called" << std::endl;
	this->name = "Default";
	this->hitPoints = 10;
	this->energyPoints = 10;
	this->attackDamage = 0;
}

ClapTrap::ClapTrap(std::string name)
{
	std::cout << "ClapTrap constructor called" << std::endl;
	this->name = name;
	this->hitPoints = 10;
	this->energyPoints = 10;
	this->attackDamage = 0;
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap Destructor called" << std::endl;
}


ClapTrap::ClapTrap(ClapTrap const & src ) //copy constructor
{
	std::cout << "ClapTrap Copy constructor called" << std::endl;
	*this = src;
}

ClapTrap & ClapTrap::operator=( ClapTrap const & rhs ) //assignment operator overload (assignation operator) //rhs = right hand side
{
	std::cout << "ClapTrap Assignation operator called" << std::endl;
	if (this != &rhs) // check for self-assignment
	{
		this->name = rhs.name;
		this->hitPoints = rhs.hitPoints;
		this->energyPoints = rhs.energyPoints;
		this->attackDamage = rhs.attackDamage;
	}
	return *this; // return the existing object so we can chain this operator
}

//abilities
void ClapTrap::attack(std::string const & target)
{
	if (this->energyPoints <=0)
	{
		std::cout << "ClapTrap " << this->name  << "do not have enough energy." <<std::endl;
		return ;
	}
	std::cout << "ClapTrap " << this->name << " attacks " << target << ", causing " << this->attackDamage << " points of damage!" << std::endl;
	this->energyPoints = this->energyPoints - 1;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << "ClapTrap " << this->name << " takes " << amount << " points of damage!" << std::endl;
	this->hitPoints = this->hitPoints - amount;
	if (this->hitPoints <= 0)
	{
		std::cout << "ClapTrap " << this->name << " is dead!" << std::endl;
		// delete this;
		return ;
	}
	std::cout << "ClapTrap " << this->name << " has " << this->hitPoints << " hit points!" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (this->energyPoints <=0)
	{
		std::cout << "ClapTrap " << this->name  << "do not have enough energy." <<std::endl;
		return ;
	}
	std::cout << "ClapTrap " << this->name << " is repaired for " << amount << " points!" << std::endl;
	std::cout << "ClapTrap " << this->name << " has " << this->hitPoints + amount << " hit points!" << std::endl;
	this->hitPoints = this->hitPoints + amount;
	this->energyPoints = this->energyPoints - 1;
}

