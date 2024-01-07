#include "Zombie.hpp"

Zombie* zombieHorde( int N, std::string name )
{
	Zombie *zombie_multiple = new Zombie[N]; // We create a Zombie object on the heap
	int i = 0;

	while (i < N)
	{
		zombie_multiple[i].setName(name);
		i++;
	}
	return (zombie_multiple);
}