#ifndef SPAN_HPP
# define SPAN_HPP

# include <iostream>
# include <vector>
# include <algorithm>
# include <exception>


class Span
{
private:
	unsigned int		_n;
	std::vector<int>	_v;
	Span(void); // default constructor
public:
	Span(unsigned int n);
	Span(const Span &copy);
	~Span(void);
	Span				&operator=(const Span &rhs);

	void				addNumber(int n);
	void				addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end);
	int					shortestSpan(void);
	int					longestSpan(void);
	class				FullException : public std::exception
	{
		virtual const char* what() const throw();
	};
	class				NoSpanException : public std::exception
	{
		virtual const char* what() const throw();
	};
};

#endif