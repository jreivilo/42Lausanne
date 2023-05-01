#ifndef WHATEVER_HPP
# define WHATEVER_HPP

template <typename T> // template <class T> is also valid //t is a placeholder for a type that will be specified later

void swap(T &a, T &b) // &a and &b are references to the objects passed as arguments
{
	T tmp = a;
	a = b;
	b = tmp;
}

template <typename T>

T min(T a, T b) // T is a type parameter //return type is T
{
	return (a < b ? a : b); //ternary operator //if a < b, return a, else return b
}

template <typename T>

T max(T a, T b) //return type is T
{
	return (a > b ? a : b); //ternary operator //if a > b, return a, else return b
}

//the objective of this exercise is to create a template function that can take any type of arguments and return the minimum or maximum of them
//it works with any type of arguments because the type is specified when the function is called

#endif