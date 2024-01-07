#include "Zombie.hpp"

int main()
{
	Zombie *zombie = newZombie("Joe"); // newZombie() returns a pointer to a Zombie object
	zombie->announce(); // We can use the -> operator to access the object's methods
	delete zombie; // We need to delete the object to avoid memory leaks
	randomChump("Patrick"); // randomChump() creates a Zombie object on the stack and calls its announce() method and then destroys the object
	return (0);
}