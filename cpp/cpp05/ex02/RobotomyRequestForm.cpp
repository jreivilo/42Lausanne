#include "RobotomyRequestForm.hpp"
#include <cstdlib>
RobotomyRequestForm::RobotomyRequestForm(std::string const target) : Form("RobotomyRequestForm", 72, 45), target(target)
{
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const & src) : Form(src), target(src.target)
{
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

RobotomyRequestForm & RobotomyRequestForm::operator=(RobotomyRequestForm const & rhs)
{
	if (this != &rhs)
	{
		Form::operator=(rhs); //
	}
	return *this;
}

void	RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() > this->getGradeToExecute())
		throw Form::GradeTooLowException();
	else if (!this->getIsSigned())
		throw Form::FormNotSignedException();
	else
	{
		std::cout << "Brrr"	<< std::endl;
		//PRINT SOMETHING 50% OF THE TIME
		int random = std::rand() % 2;
		if (random == 0)
			std::cout << this->target << " has been robotomized successfully." << std::endl;
		else
			std::cout << this->target << " has not been robotomized successfully." << std::endl;
	}
}
