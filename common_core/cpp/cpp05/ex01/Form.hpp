#ifndef FORM_HPP
# define FORM_HPP

#include <iostream>
#include <string>
#include <exception>

#include "Bureaucrat.hpp"

class Bureaucrat; // forward declaration to avoid circular dependency // sinon ca marche pas hein
//faut declarer sinon il va chercher la classe bureaucrat dans le .hpp et il la trouve pas
//le compilateur en pls sinon

class Form
{
	private:
		std::string const name;
		bool isSigned;
		int const gradeToSign;
		int const gradeToExecute;
		Form(); // default constructor in private because we don't want to use it
	public:
		Form(std::string const & name, int gradeToSign, int gradeToExecute);
		Form(Form const & src);
		~Form();
		Form & operator=(Form const & rhs);

		std::string const & getName() const;
		bool getIsSigned() const;
		int getGradeToSign() const;
		int getGradeToExecute() const;
		void beSigned(Bureaucrat const & bureaucrat);

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

std::ostream & operator<<(std::ostream & o, Form const & rhs);

#endif

