#include "Span.hpp"

Span::Span(unsigned int n) : _n(n)
{
}

Span::Span(const Span &copy)
{
	*this = copy;
}

Span::~Span(void)
{
}

Span				&Span::operator=(const Span &rhs)
{
	if (this != &rhs)
	{
		this->_n = rhs._n;
		this->_v = rhs._v;
	}
	return (*this);
}

void				Span::addNumber(int n)
{
	if (this->_v.size() == this->_n)
		throw Span::FullException();
	this->_v.push_back(n); // add n to the end of vector
}

void				Span::addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	if (this->_v.size() + std::distance(begin, end) > this->_n)
		throw Span::FullException();
	this->_v.insert(this->_v.end(), begin, end); // add elements from begin to end to the end of vector
}

int					Span::shortestSpan(void)
{
	if (this->_v.size() <= 1) //if size of vector is 0 or 1 then throw exception
		throw Span::NoSpanException();
	std::vector<int> v = this->_v; // copy vector
	std::sort(v.begin(), v.end()); // sort vector
	int min = v[1] - v[0]; // min is difference between first and second elements
	for (std::vector<int>::iterator it = v.begin(); it != v.end() - 1; it++)
	{
		if (*(it + 1) - *it < min) //if difference between next and current elements is less than min
			min = *(it + 1) - *it; // then min is difference between next and current elements
	}
	return (min);
}

int					Span::longestSpan(void)
{
	if (this->_v.size() <= 1) //if size of vector is 0 or 1 then throw exception
		throw Span::NoSpanException();
	std::vector<int> v = this->_v;
	std::sort(v.begin(), v.end());
	return (v[v.size() - 1] - v[0]); // return difference between last and first elements of sorted vector
}

const char* Span::FullException::what() const throw()
{
	return ("Span is full");
}

const char* Span::NoSpanException::what() const throw()
{
	return ("Span has no span");
}

