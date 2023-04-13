
#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(std::string const & name, int grade) : name(name) //we can initialize the const member name in the initialization list but not the grade
{
	// The throw keyword throws an exception when a problem is detected, which lets us create a custom error.
	try //try block
	{
		if (grade < 1)
			throw Bureaucrat::GradeTooHighException(); //trhowing an exception of type GradeTooHighException (which is a class) and we are using the constructor of this class
		else if (grade > 150)
			throw Bureaucrat::GradeTooLowException();
		else
			this->grade = grade;
	}
	catch (std::exception & e) //catch block
	{
		std::cout << e.what() << std::endl; //.what() is a method of the exception class
	}
}

Bureaucrat::Bureaucrat(Bureaucrat const & src) : name(src.name) //force to use the initialization list to initialize the const member name because it is const!
{
	*this = src;
}
 
Bureaucrat::~Bureaucrat()
{
}

Bureaucrat & Bureaucrat::operator=(Bureaucrat const & rhs)
{
	if (this != &rhs)
	{
		this->grade = rhs.grade;
	}
	return *this;
}

std::string const & Bureaucrat::getName() const
{
	return this->name;
}

int Bureaucrat::getGrade() const
{
	return this->grade;
}

void Bureaucrat::incrementGrade()
{
	if (this->grade == 1)
		throw Bureaucrat::GradeTooHighException();
	else
		this->grade--;
}

void Bureaucrat::decrementGrade()
{
	if (this->grade == 150)
		throw Bureaucrat::GradeTooLowException();
	else
		this->grade++;
}

const char* Bureaucrat::GradeTooHighException::what() const throw()  
{
	return "Grade too high";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Grade too low";
}

std::ostream & operator<<(std::ostream & o, Bureaucrat const & rhs)
{
	o << rhs.getName() << ", bureaucrat grade " << rhs.getGrade() << std::endl;
	return o;
}
