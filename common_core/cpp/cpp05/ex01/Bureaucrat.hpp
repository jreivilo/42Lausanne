#ifndef	BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <exception>

#include "Form.hpp"

class Form; // forward declaration to avoid circular dependency
//la meme chose que dans le .hpp de form ... sinon ca marche pas hein

class Bureaucrat
{
	private:
		std::string const name;
		int grade; //not const because we can increment and decrement it
		Bureaucrat(); // default constructor in private because we don't want to use it
	public:
		Bureaucrat(std::string const & name, int grade);
		Bureaucrat(Bureaucrat const & src);
		~Bureaucrat();
		Bureaucrat & operator=(Bureaucrat const & rhs);

		std::string const & getName() const;
		int getGrade() const;
		void incrementGrade();
		void decrementGrade();

		void signForm(Form & form);

		class GradeTooHighException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class GradeTooLowException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

std::ostream & operator<<(std::ostream & o, Bureaucrat const & rhs);

#endif
