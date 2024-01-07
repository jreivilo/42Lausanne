#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	{
		try
		{
			PresidentialPardonForm Trump("Trump_Junior");
			Bureaucrat Hillary("Hillary", 10);
			Hillary.signForm(Trump);
			Hillary.executeForm(Trump);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "......................" << std::endl;
	{
		try
		{
			PresidentialPardonForm Trump("Trump_Junior");
			Bureaucrat Hillary("Hillary", 3);
			Hillary.signForm(Trump);
			Hillary.executeForm(Trump);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "......................" << std::endl;
	{
		try
		{
			PresidentialPardonForm Trump("Trump_Junior");
			Bureaucrat Hillary("Hillary", 135);
			Hillary.signForm(Trump);
			Hillary.executeForm(Trump);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "......................" << std::endl;
	{
		try
		{
			PresidentialPardonForm Trump("Trump_Junior");
			Bureaucrat Hillary("Hillary", 2);
			// hradoux.signForm(sorrysorrymybad);
			Hillary.executeForm(Trump);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "......................" << std::endl;

	{
			try
			{
				ShrubberyCreationForm tree("jardin");
				Bureaucrat john("john", 120);
				john.signForm(tree);
				john.executeForm(tree);
			}
			catch (std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
	}
	std::cout << "......................" << std::endl;
	{
		try
	 	{
			RobotomyRequestForm brain("dead");
			Bureaucrat john("john", 1);
			john.signForm(brain);
			for(int i = 0; i < 10; i++)
			{
				john.executeForm(brain);
			}
			brain.execute(john);
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	std::cout << "......................" << std::endl;
	{
		// Bureaucrat john("john", 1);
		// RobotomyRequestForm brain("dead");
		// RobotomyRequestForm brain2 = brain;
		// john.signForm(brain2);
		// john.executeForm(brain2);
		// try
		// {
		// 	john.executeForm(brain);
		// }
		// catch(const std::exception& e)
		// {
		// 	std::cerr << e.what() << '\n';
		// }
	}
}

