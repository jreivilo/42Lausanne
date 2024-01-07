#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

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
		Intern someRandomIntern = Intern();
		Form* rrf;
		rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		Bureaucrat john("john", 1);
		john.signForm(*rrf);
		for(int i = 0; i < 10; i++)
		{
			john.executeForm(*rrf);
		}
		std::cout << *rrf << std::endl;
	}
	std::cout << "......................" << std::endl;
}


