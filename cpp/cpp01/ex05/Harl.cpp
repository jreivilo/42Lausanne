#include "Harl.hpp"

Harl::Harl()
{
}

Harl::~Harl()
{
}

void	Harl::complain( std::string level )
{
	void	(Harl::*func)(void);
	func = NULL;
	if (level == "debug")
		func = &Harl::debug;
	else if (level == "info")
		func = &Harl::info;
	else if (level == "warning")
		func = &Harl::warning;
	else if (level == "error")
		func = &Harl::error;
	(this->*func)();
}

void	Harl::debug(void)
{
	std::cout << "I'm a debug message" << std::endl;
}

void	Harl::info(void)
{
	std::cout << "I'm an info message" << std::endl;
}

void	Harl::warning(void)
{
	std::cout << "I'm a warning message" << std::endl;
}

void	Harl::error(void)
{
	std::cout << "I'm an error message" << std::endl;
}
