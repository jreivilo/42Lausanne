#include "PmergeMe.hpp"

int main(int argc, char ** argv)
{
	// std::cout << "Usage: ./pmergeme <int> <int> <int> ..." << std::endl;
	if (argc <= 2)
	{
		std::cout << "Not enough arguments!" << std::endl;
		return (1);
	}

	std::vector<int> v;
	std::list<int> l;
	try
	{
		for (int i = 1; i < argc; i++)
		{
			if (std::atoi(argv[i]) <= 0)
			{
				std::cout << "Invalid argument!" << std::endl;
				return (1);
			}
			v.push_back(std::atoi(argv[i]));
			l.push_back(std::atoi(argv[i]));
		}
		PmergeMe pmm(3);

		std::cout << "Before: ";
		PmergeMe::printVector(v);

		const clock_t begin_time = clock();
		pmm.splitVector(v);
		pmm.mergeVector(v);
		const clock_t end_time = clock() - begin_time;

		const clock_t begin_time2 = clock();
		pmm.splitlist(l);
		pmm.mergelist(l);
		const clock_t end_time2 = clock() - begin_time2;

		std::cout << "After: ";
		PmergeMe::printVector(v);

		std::cout << "Time to process a range of " << v.size() << " elements with std::[] : " << std::fixed << double(end_time) / CLOCKS_PER_SEC << " us" << std::endl; // "us" = "microseconds
		std::cout << "Time to process a range of " << l.size() << " elements with std::[] : " << std::fixed << double(end_time2) / CLOCKS_PER_SEC << " us" << std::endl; // "us" = "microseconds
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

}