#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main(int argc, char ** argv)
{

{
	(void) argc;
	(void) argv;

	std::cout << "------------------" << std::endl;
	ScavTrap a("ScavTrap");
	ScavTrap b(a);
	// ScavTrap c = b;
	// ScavTrap d;
	// d = c;


}

{	
	(void) argc;
	(void) argv;

	std::cout << "------------------" << std::endl;
	ScavTrap scavTrap("ScavTrap");
	scavTrap.attack("target");
	scavTrap.takeDamage(10);
	scavTrap.guardGate();
	scavTrap.beRepaired(10);
	scavTrap.guardGate();
}


{
	(void) argc;
	(void) argv;

	std::cout << "------------------" << std::endl;
	FragTrap fragTrap("FragTrap");
	fragTrap.attack("target");
	fragTrap.takeDamage(10);
	fragTrap.highFivesGuys();
	fragTrap.beRepaired(10);
	fragTrap.highFivesGuys();
}

std::cout << "------------------" << std::endl;
return 0;

}

