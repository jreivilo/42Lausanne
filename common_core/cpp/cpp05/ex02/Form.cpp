#include "Form.hpp"

Form::Form(std::string const & name, int gradeToSign, int gradeToExecute) : name(name), isSigned(false), gradeToSign(gradeToSign), gradeToExecute(gradeToExecute)
{
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw Form::GradeTooHighException();
	else if (gradeToSign > 150 || gradeToExecute > 150)
		throw Form::GradeTooLowException();
}

Form::Form(Form const & src) : name(src.name), isSigned(src.isSigned), gradeToSign(src.gradeToSign), gradeToExecute(src.gradeToExecute)
{
}

Form::~Form()
{
}

Form & Form::operator=(Form const & rhs)
{
	if (this != &rhs)
	{
		this->isSigned = rhs.isSigned;
	}
	return *this;
}

std::string const & Form::getName() const
{
	return this->name;
}

bool Form::getIsSigned() const
{
	return this->isSigned;
}

int Form::getGradeToSign() const
{
	return this->gradeToSign;
}

int Form::getGradeToExecute() const
{
	return this->gradeToExecute;
}

void Form::beSigned(Bureaucrat const & bureaucrat)
{
	if (bureaucrat.getGrade() > this->gradeToSign)
		throw Form::GradeTooLowException();
	else
		this->isSigned = true;
}

void Form::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() > this->getGradeToExecute())
		throw Form::GradeTooLowException();
	else if (!this->getIsSigned())
		throw Form::FormNotSignedException();
	else
		std::cout << this->name << " has been executed." << std::endl;
}

const char* Form::GradeTooHighException::what() const throw()
{
	return "Grade too high";
}

const char* Form::GradeTooLowException::what() const throw()
{
	return "Grade too low";
}

const char* Form::FormNotSignedException::what() const throw()
{
	return "Form not signed";
}


std::ostream & operator<<(std::ostream & o, Form const & rhs)
{
	o << rhs.getName() << ", form grade to sign " << rhs.getGradeToSign() << ", form grade to execute " << rhs.getGradeToExecute() << ", form is signed " << rhs.getIsSigned() << std::endl;
	return o;
}

// Path: cpp\cpp05\ex01\main.cpp