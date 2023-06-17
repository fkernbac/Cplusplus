#include "PmergeMe.hpp"
#include <cctype>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <ctime>

/* CONSTRUCTORS ==============================================================*/

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(std::string& sequence)
{
	std::istringstream	iss(sequence);
	int					num;

	_unorderedNumbers = 0;

	while (iss >> num)
	{
		_vector.push_back(num);
		_unsortedList.push_back(num);
		_unorderedNumbers++;
	}
	if (!iss.eof())
		throw std::runtime_error("Error: input string could not be parsed.");
}

PmergeMe::PmergeMe(const PmergeMe& other) : _unorderedNumbers(other._unorderedNumbers), _vector(other._vector), _unsortedList(other._unsortedList) {}

PmergeMe&	PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vector = other._vector;
		_unsortedList = other._unsortedList;
		_unorderedNumbers = other._unorderedNumbers;
	}

	return (*this);
}

PmergeMe::~PmergeMe() {}


/* PRIVATE FUNCTIONS =========================================================*/

void	PmergeMe::_generateInsertionSequence()
{
	int	lastJacobsthal = 0;

	_insertionSequence.clear();

	for (std::vector<int>::iterator it = _jacobsthal.begin(); it != _jacobsthal.end(); it++)
	{
		for (int j = *it; j > lastJacobsthal; j--)
			_insertionSequence.push_back(j - 1);
		lastJacobsthal = *it;
	}
}

void	PmergeMe::_generateJacobsthal()
{
	_jacobsthal.clear();

	int	beforeLast = 0;
	int	last = 1;

	while (last < _unorderedNumbers)
	{
		int	j = last + 2 * beforeLast;
		_jacobsthal.push_back(j);

		beforeLast = last;
		last = j;
	}
}

/* FUNCTIONS =================================================================*/

void	PmergeMe::printVector()
{
	for (std::vector<int>::const_iterator it = _vector.begin(); it != _vector.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void	PmergeMe::printList()
{
	for (std::list<int>::const_iterator it = _unsortedList.begin(); it != _unsortedList.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void	PmergeMe::printSortedList()
{
	for (std::list<int>::const_iterator it = _sortedList.begin(); it != _sortedList.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void	PmergeMe::printResult()
{
	//sort vector
	clock_t	startTime = clock();
	_sortVector();
	clock_t	endTime = clock();

	double	elapsedTime = static_cast<double>(endTime - startTime);

	std::cout << "Vector sorted in " << elapsedTime << " \n";
	printVector();

	//sort list
	startTime = clock();
	_sortList();
	endTime = clock();
	elapsedTime = static_cast<double>(endTime - startTime);

	std::cout << "List sorted in " << elapsedTime << " \n";
	printList();
}
