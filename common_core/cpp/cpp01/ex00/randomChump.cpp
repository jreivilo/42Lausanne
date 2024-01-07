#include "Zombie.hpp"

void randomChump( std::string name )
{
	Zombie zombie = Zombie(name); // We create a Zombie object on the stack
	zombie.announce();
}