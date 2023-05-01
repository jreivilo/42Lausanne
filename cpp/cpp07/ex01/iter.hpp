#ifndef ITER_HPP
# define ITER_HPP

#include <iostream>

template <typename T>

void iter(T *array, int length, void (*f)(T const &)) //first argument is a pointer to the first element of an array of type T, second argument is the number of elements in the array, third argument is a pointer to a function that takes a reference to a constant T as a parameter and returns void
{
	for (int i = 0; i < length; i++)
	{
		f(array[i]);
	}
}

#endif