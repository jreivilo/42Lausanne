#include "Zombie.hpp"

// Zombie::Zombie(std::string name)
// {
// 	this->name = name;
// 	std::cout << "Zombie created" << std::endl;
// }

Zombie::Zombie()
{
	std::cout << "Zombie created" << std::endl;
}

Zombie::~Zombie()
{
	std::cout << this->name << " (Zombie) destroyed" << std::endl;
}

void	Zombie::setName(std::string name)
{
	this->name = name;
}

void	Zombie::announce(void)
{
	std::cout << this->name << " BraiiiiiiinnnzzzZ..." << std::endl;
}