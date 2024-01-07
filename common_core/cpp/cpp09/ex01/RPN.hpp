#ifndef RNN_HPP
# define RNN_HPP

# include <iostream>
# include <string>
# include <exception>
# include <vector>
# include <deque>
# include <list>
# include <algorithm>
# include <iterator>
# include <sstream>
# include <cmath>

class RPN
{
	private:
		//create a stack
		std::deque<int> stack;
	
	public:
		RPN();
		RPN(std::string str);
		RPN(RPN const & src);
		~RPN();
		RPN & operator=(RPN const & rhs);

		void add();
		void subtract();
		void multiply();
		void divide();

		int getNumber();

		class EmptyStackException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class NotEnoughValuesException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class DivisionByZeroException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class MoreThanOneNumberException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class InvalidTokenException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		
};

#endif