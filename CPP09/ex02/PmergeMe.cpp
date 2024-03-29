#include "PmergeMe.hpp"
#include <cctype>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <iomanip>

/* CONSTRUCTORS ==============================================================*/

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(std::string& sequence)
{
	std::istringstream	iss(sequence);
	int					num;

	while (iss >> num)
	{
		if (num < 0)
			throw std::runtime_error("Error: negative numbers are not allowed.");
		_unsorted.push_back(num);
	}

	//check for problematic user input
	if (!iss.eof())
		throw std::runtime_error("Error: input string could not be parsed.");
	if (_unsorted.size() <= 1)
		throw std::runtime_error("Error: no point in sorting 1 number");

	_pairVector.reserve(_unsorted.size());
}

PmergeMe::PmergeMe(const PmergeMe& other) : _unsorted(other._unsorted) {}

PmergeMe&	PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_unsorted = other._unsorted;
	}

	return (*this);
}

PmergeMe::~PmergeMe() {}


/* PRIVATE FUNCTIONS =========================================================*/

void	PmergeMe::_generateJacobsthal()
{
	// Initial Jacobsthal numbers
	int	lastIndex = _unsorted.size() / 2;
	int beforelast = 1;
	int last = 1;

	// Clear the existing sequence
	_jacobsthal.clear();

	// Generate Jacobsthal sequence
	while (last < lastIndex)
	{
		int	next = last + 2 * beforelast;
		if (next >= lastIndex)
			break;
		_jacobsthal.push_back(next);

		beforelast = last;
		last = next;
	}

	// Make the last jacobsthal number the last index
	_jacobsthal.push_back(lastIndex);
}

/* FUNCTIONS =================================================================*/

/*Returns true if a->second < b->second.*/
bool	PmergeMe::comparePairs(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
	return a.second < b.second;
}

/*Prints the original sequence.*/
void	PmergeMe::printUnsorted()
{
	for (std::vector<int>::const_iterator it = _unsorted.begin(); it != _unsorted.end(); ++it)
		std::cout << *it << " ";

	std::cout << "\n";
}

/*Prints the pairs in the vector.*/
void	PmergeMe::printPairVector()
{
	for (std::vector<std::pair<int, int> >::const_iterator it = _pairVector.begin(); it != _pairVector.end(); ++it)
		std::cout << "(" << it->first << ", " << it->second << ") ";

	std::cout << "\n";
}

/*Prints the main chain of the vector.*/
void	PmergeMe::printVector()
{
	for (std::vector<std::pair<int, int> >::const_iterator it = _pairVector.begin(); it != _pairVector.end(); it++)
		std::cout << it->second << " ";

	std::cout << "\n";
}

/*Prints the main chain of the list.*/
void	PmergeMe::printList()
{
	for (std::list<std::pair<int, int> >::const_iterator it = _pairList.begin(); it != _pairList.end(); ++it)
		std::cout << it->second << " ";

	std::cout << "\n";
}

/*Prints the pairs in the list.*/
void	PmergeMe::printPairList()
{
	for (std::list<std::pair<int, int> >::const_iterator it = _pairList.begin(); it != _pairList.end(); ++it)
		std::cout << "(" << it->first << ", " << it->second << ") ";

	std::cout << "\n";
}

/*Sorts the given sequence and prints the times.*/
void	PmergeMe::printResult()
{
	//sort vector
	clock_t	startTime = clock();
	_sortVector();
	clock_t	endTime = clock();

	double	timeVector = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC * 1000;

	// sort list
	startTime = clock();
	_sortList();
	endTime = clock();

	double	timeList = static_cast<double>(endTime - startTime) * 1000 / CLOCKS_PER_SEC;

	//print unsorted sequence
	std::cout << "Before:\t";
	printUnsorted();
	std::cout << "After:\t";
	printVector();
	// std::cout << "After:\t";
	// printList();

	//print times
	std::cout << std::fixed << std::setprecision(3) << "Time to process a range of " << _unsorted.size() << " elements with std::vector: " << timeVector << " ms\n";
	std::cout << std::fixed << std::setprecision(3) << "Time to process a range of " << _unsorted.size() << " elements with std::list:   " << timeList << " ms\n";
}
