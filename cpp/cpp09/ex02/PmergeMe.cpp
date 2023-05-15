#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : _n(0)
{}

PmergeMe::PmergeMe(int n) : _n(n)
{}

PmergeMe::PmergeMe(PmergeMe const & src) : _n(src.getN())
{
	*this = src;
}

PmergeMe::~PmergeMe()
{
}

PmergeMe & PmergeMe::operator=(PmergeMe const & rhs)
{
	if (this != &rhs)
	{
		// this->_n = rhs._n;
	}
	return (*this);
}

int PmergeMe::getN() const
{
	return (this->_n);
}

void PmergeMe::printVector(std::vector<int> &v)
{
	for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void PmergeMe::printlist(std::list<int> &l)
{
	for (std::list<int>::iterator it = l.begin(); it != l.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void PmergeMe::sortVector(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	std::sort(begin, end);
}

void PmergeMe::sortlist(std::list<int>::iterator begin, std::list<int>::iterator end)
{
	for (std::list<int>::iterator it = begin; it != end; it++)
	{
		for (std::list<int>::iterator it2 = begin; it2 != end; it2++)
		{
			if (*it < *it2)
			{
				int tmp = *it;
				*it = *it2;
				*it2 = tmp;
			}
		}
	}
}

void PmergeMe::splitVector(std::vector<int> &v)
{
	if (v.size() < (unsigned int)this->_n)
		throw WrongN();
	for (int i = 0; i < _n; i++)
	{
		sortVector(v.begin() + i * (v.size() / _n), v.begin() + (i + 1) * (v.size() / _n));
	}	
}

//operator overload + std::_List_iterator<int>

std::list<int>::iterator operator+(std::list<int>::iterator it, int n)
{
	for (int i = 0; i < n; i++)
		it++;
	return (it);
}

std::list<int>::iterator operator-(std::list<int>::iterator it, int n)
{
	for (int i = 0; i < n; i++)
		it--;
	return (it);
}

bool vector_is_sorted(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	for (std::vector<int>::iterator it = begin; it != end - 1; it++)
	{
		if (*it > *(it + 1))
			return (false);
	}
	return (true);
}

bool list_is_sorted(std::list<int>::iterator begin, std::list<int>::iterator end)
{
	for (std::list<int>::iterator it = begin; it != end - 1; it++)
	{
		if (*it > *(it + 1))
			return (false);
	}
	return (true);
}

void PmergeMe::splitlist(std::list<int> &l)
{
	if (l.size() < (unsigned int)this->_n)
		throw WrongN();
	for (int i = 0; i < _n; i++)
	{
		sortlist(l.begin() + i * (l.size() / _n), l.begin() + (i + 1) * (l.size() / _n));
	}	
}

void PmergeMe::mergeVector(std::vector<int> &v)
{
	int y = 0;
	if (v.size() < (unsigned int)this->_n)
		throw WrongN();
	while (vector_is_sorted(v.begin(), v.end()) == false)
	{
		for (int i = 0; i < _n - y; i++)
		{
			sortVector(v.begin() + i * (v.size() / (_n - y)), v.begin() + (i + 1) * (v.size() / (_n - y)));
		}
		y++;
	}
}

void PmergeMe::mergelist(std::list<int> &l)
{
	int y = 0;
	if (l.size() < (unsigned int)this->_n)
		throw WrongN();
	while (list_is_sorted(l.begin(), l.end()) == false)
	{
		for (int i = 0; i < _n - y; i++)
		{
			sortlist(l.begin() + i * (l.size() / (_n - y)), l.begin() + (i + 1) * (l.size() / (_n - y)));
		}
		y++;
	}
}


const char* PmergeMe::NotEnoughValuesException::what() const throw()
{
	return ("Not enough values!");
}

const char* PmergeMe::WrongN::what() const throw()
{
	return ("Wrong N!");
}

