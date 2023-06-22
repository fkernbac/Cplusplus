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

	while (iss >> num)
	{
		_unsortedVector.push_back(num);
	}

	if (!iss.eof())
		throw std::runtime_error("Error: input string could not be parsed.");
}

PmergeMe::PmergeMe(const PmergeMe& other) : _unsortedVector(other._unsortedVector) {}

PmergeMe&	PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_unsortedVector = other._unsortedVector;
	}

	return (*this);
}

PmergeMe::~PmergeMe() {}


/* PRIVATE FUNCTIONS =========================================================*/

void	PmergeMe::_generateJacobsthal()
{
	// Initial Jacobsthal numbers
	int beforelast = 1;
	int last = 1;

	// Clear the existing sequence
	_jacobsthal.clear();

	// Generate Jacobsthal sequence
	while ((unsigned long) last <= _unsortedVector.size() / 2)		//needs fixing
	{
		int	next = last + 2 * beforelast;
		_jacobsthal.push_back(next);

		beforelast = last;
		last = next;
		}

	std::vector<int>::iterator	lastIndex = _jacobsthal.end() - 1;

	while ((unsigned long) *lastIndex > _unsortedVector.size() / 2)
		*lastIndex = *lastIndex - 1;

	// _jacobsthal.clear();

	// int	beforeLast = 0;
	// int	last = 1;

	// while ((unsigned long) last <= _unsortedList.size())
	// {
	// 	int	j = last + 2 * beforeLast;
	// 	_jacobsthal.push_back(j);

	// 	beforeLast = last;
	// 	last = j;
	// }
}

/* FUNCTIONS =================================================================*/

bool	PmergeMe::comparePairs(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
	return a.second < b.second;
}

void	PmergeMe::printPairVector()
{
	for (std::vector<std::pair<int, int> >::const_iterator it = _pairVector.begin(); it != _pairVector.end(); ++it)
		std::cout << "(" << it->first << ", " << it->second << ") ";

	std::cout << "\n";
}

void	PmergeMe::printVector()
{
	for (std::vector<int>::const_iterator it = _unsortedVector.begin(); it != _unsortedVector.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void	PmergeMe::printPairList()
{
	for (std::list<std::pair<int, int> >::const_iterator it = _pairList.begin(); it != _pairList.end(); ++it)
		std::cout << "(" << it->first << ", " << it->second << ") ";

	std::cout << "\n";
}

void	PmergeMe::printResult()
{
	//sort vector
	clock_t	startTime = clock();
	_sortVector();
	clock_t	endTime = clock();

	double	elapsedTime = static_cast<double>(endTime - startTime);

	std::cout << "Vector sorted in " << elapsedTime << " \n";
	printPairVector();

	// sort list
	startTime = clock();
	_sortList();
	endTime = clock();
	elapsedTime = static_cast<double>(endTime - startTime);

	std::cout << "List sorted in " << elapsedTime << " \n";
	printPairList();
}
