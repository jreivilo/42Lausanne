#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{

{
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	j->makeSound(); //will output the cat sound!
	i->makeSound();
	meta->makeSound();
	delete meta;
	delete i;
	delete j;
}
std::cout << "------------------------" << std::endl;
{
	const WrongAnimal* meta = new WrongAnimal();
	const WrongAnimal* j = new WrongCat();
	std::cout << j->getType() << " " << std::endl;
	j->makeSound(); //will output the cat sound!
	meta->makeSound();
	delete meta;
	delete j;
}
std::cout << "------------------------" << std::endl;
}


// deleting object of polymorphic class type  
// Animal’ which has non-virtual destructor might cause undefined behavior