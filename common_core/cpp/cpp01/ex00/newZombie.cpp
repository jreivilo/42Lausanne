#include "Zombie.hpp"

Zombie* newZombie( std::string name )
{
	Zombie *zombie = new Zombie(name); // We create a Zombie object on the heap
	return (zombie);
}