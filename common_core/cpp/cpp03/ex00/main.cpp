#include "ClapTrap.hpp"




int main(int argc, char ** argv)
{
	(void) argc;
	(void) argv;

	std::cout << "Building..." << std::endl;
	ClapTrap a;
	ClapTrap b("B");

	//newline
	std::cout << std::endl;
	std::cout << "Attack" << std::endl;
	a.attack("B");
	b.attack("C");

	std::cout << std::endl;
	std::cout << "TakeDamage" << std::endl;
	a.takeDamage(9);
	b.takeDamage(7);

	std::cout << std::endl;
	std::cout << "Repaired" << std::endl;
	a.beRepaired(5);
	b.beRepaired(7);

	std::cout << std::endl;
}

// int main(int argc, char ** argv)
// {
// 	(void) argc;
// 	(void) argv;

// 	std::cout << "Building..." << std::endl;
// 	ClapTrap a;
// 	ClapTrap b("B");
// 	ClapTrap c(b);
// 	ClapTrap d;
// 	d = c;

// 	//newline
// 	std::cout << std::endl;
// 	std::cout << "Attack" << std::endl;
// 	a.attack("B");
// 	b.attack("C");
// 	c.attack("D");
// 	d.attack("A");

// 	std::cout << std::endl;
// 	std::cout << "TakeDamage" << std::endl;
// 	a.takeDamage(9);
// 	b.takeDamage(7);
// 	c.takeDamage(5);
// 	d.takeDamage(3);

// 	std::cout << std::endl;
// 	std::cout << "Repaired" << std::endl;
// 	a.beRepaired(5);
// 	b.beRepaired(7);
// 	c.beRepaired(9);
// 	d.beRepaired(11);

// 	std::cout << std::endl;

// 	return 0;
// }