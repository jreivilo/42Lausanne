#include "Intern.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "ShrubberyCreationForm.hpp"

Intern::Intern()
{
}

Intern::Intern(Intern const & src)
{
	*this = src;
}

Intern::~Intern()
{
}

Intern & Intern::operator=(Intern const & rhs)
{
	if (this != &rhs)
	{
	}
	return *this;
}

Form *	Intern::makeForm(std::string const & formName, std::string const & target) const
{
	Form *form = NULL;

	std::string formNames[3] = {"presidential pardon", "robotomy request", "shrubbery creation"};
	Form* (Intern::*formFunctions[3])(std::string const & target) const = {&Intern::makePresidentialPardonForm, &Intern::makeRobotomyRequestForm, &Intern::makeShrubberyCreationForm};
	//form* cest ce qui rend
	//intern::*formFunctions[3] = CEST LA FUNCTION
	//std::string const & target) const = CEST LE PARAMETRE
	for (int i = 0; i < 3; i++)
	{
		if (formName == formNames[i])
		{
			std::cout << "Intern creates " << formName << std::endl;
			form = (this->*formFunctions[i])(target);
			return form;
		}
	}
	std::cout << "Form not found" << std::endl;
	return form;
}

Form *	Intern::makePresidentialPardonForm(std::string const & target) const
{
	return new PresidentialPardonForm(target);
}

Form *	Intern::makeRobotomyRequestForm(std::string const & target) const
{
	return new RobotomyRequestForm(target);
}

Form *	Intern::makeShrubberyCreationForm(std::string const & target) const
{
	return new ShrubberyCreationForm(target);
}


