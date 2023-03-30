#include "ClapTrap.hpp"

int main(int argc, char ** argv)
{
	(void) argc;
	(void) argv;

	std::cout << "Building..." << std::endl;
	ClapTrap a;
	ClapTrap b("B");
	ClapTrap c(b);
	ClapTrap d;
	d = c;

	//newline
	std::cout << std::endl;
	std::cout << "Attack" << std::endl;
	a.attack("B");
	b.attack("C");
	c.attack("D");
	d.attack("A");

	std::cout << std::endl;
	std::cout << "TakeDamage" << std::endl;
	a.takeDamage(11);
	b.takeDamage(5);
	c.takeDamage(5);
	d.takeDamage(5);

	std::cout << std::endl;
	std::cout << "Repaired" << std::endl;
	a.beRepaired(5);
	b.beRepaired(5);
	c.beRepaired(5);
	d.beRepaired(5);

	std::cout << std::endl;
	std::cout << "Display" << std::endl;


	return 0;
}