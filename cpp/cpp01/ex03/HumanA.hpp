#ifndef HUMANa_HPP
#define HUMANA_HPP

#include <iostream>
#include <string>
#include "Weapon.hpp"

class HumanA
{
	private:
		std::string name;
		Weapon &weapon; //This is a reference, not a pointer.
	public:
		HumanA(std::string name, Weapon &weapon);
		~HumanA();
		void attack();
};

//Pointers and references are essentially the same thing, regarding how the computer will do with them. 
//Pointers are more flexible than references. 
//If something should always exist and never change, use a references. 
//But if it should not always exist and can change, use a pointer.

#endif