#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

# include "Form.hpp"

#include <iostream>
#include <string>
#include <exception>

class	PresidentialPardonForm : public Form
{
	public:
		PresidentialPardonForm(std::string const target);
		PresidentialPardonForm(PresidentialPardonForm const & src);
		~PresidentialPardonForm();

		PresidentialPardonForm & operator=(PresidentialPardonForm const & rhs);

		virtual void	execute(Bureaucrat const & executor) const;

	private:
		PresidentialPardonForm();
		std::string const target;
};


#endif