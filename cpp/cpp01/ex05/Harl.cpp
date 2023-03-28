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


//void	Karen::complain(std::string level)
// {
// 	void		(Karen::*ptr_complain[4])(void) = {&Karen::debug, &Karen::info, &Karen::warning, &Karen::error};
// 	std::string	levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

// 	for (int i = 0; i < 4; i++)
// 	{
// 		if (levels[i] == level)
// 		{
// 			(this->*ptr_complain[i])();
// 			break ;
// 		}
// 	}
// }
//

// This line declares an array of four pointers to class member functions of Karen. 
// The member functions are debug(), info(), warning(), and error(). The array is named ptr_complain.