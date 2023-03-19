#include "Zombie.hpp"

int main()
{
	Zombie *zombie = zombieHorde(5, "Joe"); // zombieHorde() returns a pointer to a Zombie object
	int i = 0;

	while (i < 5)
	{
		zombie[i].announce(); // We can use the -> operator to access the object's methods
		i++;
	}
	delete [] zombie; // We need to delete the object to avoid memory leaks
	return (0);
}