#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <iostream>
# include <stack>
# include <deque>

template <typename T>
class MutantStack : public std::stack<T> // std::stack is a container adapter
{
public:
	MutantStack(void) : std::stack<T>() {} // default constructor
	MutantStack(const MutantStack &copy) : std::stack<T>(copy) {}
	~MutantStack(void) {}
	MutantStack		&operator=(const MutantStack &rhs)
	{
		if (this != &rhs)
			std::stack<T>::operator=(rhs);
		return (*this);
	}

	typedef typename std::stack<T>::container_type::iterator iterator;
	iterator		begin(void) //iterator is a type of std::stack<T>::container_type::iterator
	{
		return (std::stack<T>::c.begin());
	}
	iterator		end(void)
	{
		return (std::stack<T>::c.end());
	}
};
//Member objects
// Container c
 
// the underlying container
// (protected member object)

#endif

//The std::stack class is a container adaptor that gives the programmer 
// the functionality of a stack - specifically, a LIFO (last-in, first-out) 
// data structure.