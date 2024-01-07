#include "ClapTrap.hpp"
#include "ScavTrap.hpp"		

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

std::cout << "------------------" << std::endl;
return 0;

}

