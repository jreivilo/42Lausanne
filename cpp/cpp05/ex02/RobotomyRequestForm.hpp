#ifndef ROBOTOMYREQUESTFORM_HPP
# define ROBOTOMYREQUESTFORM_HPP

#include "Form.hpp"

#include <iostream>
#include <string>
#include <exception>

class RobotomyRequestForm : public Form
{
	public:
		RobotomyRequestForm(std::string const target);
		RobotomyRequestForm(RobotomyRequestForm const & src);
		~RobotomyRequestForm();

		RobotomyRequestForm & operator=(RobotomyRequestForm const & rhs);

		virtual void	execute(Bureaucrat const & executor) const;

	private:
		RobotomyRequestForm();
		std::string const target;
};

#endif