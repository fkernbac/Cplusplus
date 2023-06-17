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
		_unorderedNumbers++;
	}
	if (!iss.eof())
		throw std::runtime_error("Error: input string could not be parsed.");

}

PmergeMe::PmergeMe(const PmergeMe& other) : _unorderedNumbers(other._unorderedNumbers), _vector(other._vector), _set(other._set) {}

PmergeMe&	PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_unorderedNumbers = other._unorderedNumbers;
	}

	return (*this);
}

PmergeMe::~PmergeMe() {}

/* FUNCTIONS =================================================================*/

void	PmergeMe::printVector()
{
	for (std::vector<int>::const_iterator it = _vector.begin(); it != _vector.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void	PmergeMe::_sortPairs()
{
	for (int i = 1; i < _size; i += 2)
		if (_vector[i - 1] > _vector[i])
			std::swap(_vector[i - 1], _vector[i]);
}

void	PmergeMe::_insertPair(int sortIndex, int compareIndex)
{
	//comparing with first element, insert at front
	//found first element that is smaller, insert behind
	if (compareIndex <= 0 || _vector[compareIndex] < _vector[sortIndex])
	{
		int	small = _vector[sortIndex - 1];
		int	big = _vector[sortIndex];

		std::vector<int>::iterator	eraseIt = _vector.begin();
		std::advance(eraseIt, sortIndex);
		_vector.erase(std::prev(eraseIt), ++eraseIt);

		std::vector<int>::iterator	insertIt = _vector.begin();
		std::advance(insertIt, compareIndex + 1);
		_vector.insert(insertIt, big);

		insertIt = _vector.begin();
		std::advance(insertIt, compareIndex + 1);
		_vector.insert(insertIt, small);

	}
	//compared element is bigger than what we're inserting, continue searching for right place
	else
		_insertPair(sortIndex, compareIndex - 2);
}

void	PmergeMe::_sortByGreater(int index)
{
	if (index <= 1)
		return ;
	_sortByGreater(index - 2);
	_insertPair(index, index - 2);
}

void	PmergeMe::_sortVector()
{
std::cout << "1. original:\n";
printVector();

	_sortPairs();

std::cout << "2. sorted pairs:\n";
printVector();

	if (_unorderedNumbers % 2 == 0)
	{
std::cout << "starting at end index " << _unorderedNumbers - 1 << "\n";
		_sortByGreater(_unorderedNumbers - 1);
	}
	else
	{
std::cout << "starting at end index " << _unorderedNumbers - 2 << "\n";
		_sortByGreater(_unorderedNumbers - 2);
	}

std::cout << "3. sorted big numbers:\n";
//at this point every 2. element and the first one form a sorted list. odd last element is ignored.
printVector();
}

void	PmergeMe::printResult()
{
	clock_t	startTime = clock();

	_sortVector();

	clock_t	endTime = clock();
	double	elapsedTime = static_cast<double>(endTime - startTime);

	std::cout << "Vector sorted in " << elapsedTime << " \n";

	for (std::vector<int>::const_iterator it = _vector.begin(); it != _vector.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}
