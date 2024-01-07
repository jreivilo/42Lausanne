#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap
{
	private:
		bool gateKeeperMode;
	public:
		FragTrap();
		FragTrap(std::string name);
		~FragTrap();

		FragTrap(FragTrap const & src);
		FragTrap & operator=(FragTrap const & rhs);
		
		void attack(std::string const & target);
		void highFivesGuys();
};

#endif
