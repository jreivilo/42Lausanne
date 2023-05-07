#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>
# include <iostream>
# include <vector>
# include <list>
# include <deque>

template <typename T>
typename T::iterator easyfind(T &container, int value) // typename T::iterator is a type of iterator of container T
{
	typename T::iterator it = std::find(container.begin(), container.end(), value); //
	if (it == container.end())
		throw std::exception();
	return (it); // return it
}

#endif