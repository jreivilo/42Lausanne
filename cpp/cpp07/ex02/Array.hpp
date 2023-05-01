#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <string>

template <typename T>
class Array
{
private:
	T*		__array;
	int		__size;
	
public:
	Array(void) : __array(NULL), __size(0) {} // default constructor 
	Array(unsigned int n) : __array(new T[n]), __size(n) {}                  //__array=new T[n] is the same as __array=new T * n
	Array(Array const & src) : __array(NULL), __size(0) { *this = src; } //array is set to NULL because it will be set in the operator= overload
	~Array(void) { delete [] __array; }

	Array&	operator=(Array const & rhs)
	{
		if (this != &rhs)
		{
			delete [] __array; // delete old array
			__size = rhs.__size;
			__array = new T[__size];
			for (int i = 0; i < __size; i++) // copy array elements
				__array[i] = rhs.__array[i];
		}
		return (*this); // return the existing object
	}

	T&		operator[](int i) // return reference to element
	{
		if (i < 0 || i >= __size) // check index
			throw std::exception(); //if out of range, throw exception
		return (__array[i]); // return reference to element
	}

	int		size(void) const { return (__size); }
};

#endif