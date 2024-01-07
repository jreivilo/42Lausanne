#ifndef INTERN_HPP
#define INTERN_HPP

#include "Form.hpp"

#include <iostream>
#include <string>
#include <exception>

class Intern
{
	public:
		Intern();
		Intern(Intern const & src);
		~Intern();

		Intern & operator=(Intern const & rhs);

		Form *	makeForm(std::string const & formName, std::string const & target) const;
		Form *	makePresidentialPardonForm(std::string const & target) const;
		Form *	makeRobotomyRequestForm(std::string const & target) const;
		Form *	makeShrubberyCreationForm(std::string const & target) const;
};

#endif