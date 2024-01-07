#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <string>
#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <list>
#include <algorithm>

class PmergeMe
{
	private:
		int const _n;

	public:
		PmergeMe();
		PmergeMe(int n);
		PmergeMe(PmergeMe const & src);
		~PmergeMe();
		PmergeMe & operator=(PmergeMe const & rhs);

		int getN() const;

		static void printVector(std::vector<int> &v);
		static void printlist(std::list<int> &l);

		void sortVector(std::vector<int>::iterator begin, std::vector<int>::iterator end);
		void sortlist(std::list<int>::iterator begin, std::list<int>::iterator end);

		void splitVector(std::vector<int> &v);
		void splitlist(std::list<int> &l);

		void mergeVector(std::vector<int> &v);
		void mergelist(std::list<int> &l);




		class NotEnoughValuesException : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

		class WrongN : public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
};

#endif