#include "ShrubberyCreationForm.hpp"

#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm(std::string const target) : Form("ShrubberyCreationForm", 145, 137), target(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const & src) : Form(src), target(src.target)
{
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

ShrubberyCreationForm & ShrubberyCreationForm::operator=(ShrubberyCreationForm const & rhs)
{
	if (this != &rhs)
	{
		Form::operator=(rhs); 
	}
	return *this;
}

void	ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() > this->getGradeToExecute())
		throw Form::GradeTooLowException();
	else if (!this->getIsSigned())
		throw Form::FormNotSignedException();
	else
	{
		std::ofstream ofs;
		std::string target_copy = this->target;
		std::string name = "_shrubbery";
		ofs.open((target_copy + name).c_str());//c_str() converts string to char*, bref ca marche
		if (ofs.is_open()) // if file is open
		{
			ofs << "         v" << std::endl;
			ofs << "        >X<" << std::endl;
			ofs << "         A" << std::endl;
			ofs << "        d$b" << std::endl;
			ofs << "      .d\\$$b." << std::endl;
			ofs << "    .d$i$$\\$$b." << std::endl;
			ofs << "   .d$$@b\\$$$ib." << std::endl;
			ofs << "  .d$$i$$b\\$$$$b." << std::endl;
			ofs << "  d$$$$@$b\\$$$$$i" << std::endl;
			ofs << " d$$$$$$i$$\\$$$$$" << std::endl;
			ofs << "d$$$$$$$$@$b\\$$$b" << std::endl;
			ofs << "$$$$$$$$$$$i$$\\$$b" << std::endl;
			ofs << "$$$$$$$$$$$$$@b\\$$b" << std::endl;
			ofs << "$$$$$$$$$$$$$$$i$$b" << std::endl;
			ofs << "$$$$$$$$$$$$$$$$@b$" << std::endl;
			ofs << "$$$$$$$$$$$$$$$$$$$" << std::endl;
			ofs << " $$$i$$$$$$$$$$$@$" << std::endl;
			ofs << "  $$$$$$$$$$$$$$$" << std::endl;
			ofs << "   $$$\\$$$$$$$$$" << std::endl;
			ofs << "    $$$$$$$$$$$" << std::endl;
			ofs << "     $$$$$$$$$" << std::endl;
			ofs << "      $$$$$$$" << std::endl;
			ofs << "       $$$$$" << std::endl;
			ofs << "        $$$" << std::endl;
			ofs << "         $" << std::endl;
			ofs.close();
		}
		std::cout << "Shrubbery created" << std::endl;
	}
}


