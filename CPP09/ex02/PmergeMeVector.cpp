#include "PmergeMe.hpp"
#include <iostream>


/* VECTOR SORTING ALGORITHM =========================================================*/

void	PmergeMe::_sortPairsVector()
{
	for (std::vector<int>::iterator it = _vector.begin() + 1; it < _vector.end(); it += 2)
		if (*(it - 1) > *it)
			std::iter_swap(it - 1, it);
}

/*Recursive function for inserting at the front.*/
void	PmergeMe::_sortByGreaterVector(std::vector<int>::iterator startIt)
{
	if (startIt <= _vector.begin() + 1)
		return;

	_sortByGreaterVector(startIt - 2);
	_insertPairVector(startIt, startIt - 2);
}

/*Recursive function for finding the right spot for insertion.*/
void	PmergeMe::_insertPairVector(std::vector<int>::iterator sortIt, std::vector<int>::iterator compareIt)
{
//this might need fixing
	if (compareIt == _vector.begin() || *compareIt < *sortIt)
		std::iter_swap(sortIt - 1, sortIt);
	else
		_insertPairVector(sortIt, compareIt - 2);
}

void	PmergeMe::_insertSmallVector()
{
	for(std::vector<int>::iterator	it = _insertionSequence.begin(); it != _insertionSequence.end(); it++)
	{
		int	vectorIndex = *it + 1;
		if (vectorIndex > _unorderedNumbers - 1)
			continue;

		int	value = _vector[vectorIndex];
		_vector.erase(_vector.begin() + vectorIndex);
		_mergeInsertVector(value);
	}
}

void	PmergeMe::_mergeInsertVector(int value)
{
	std::vector<int>::iterator	it = _vector.begin();
	while (value > *it && it != _vector.end())
		it++;

	_vector.insert(it, value);
}

void	PmergeMe::_sortVector()
{
	//1. sort pairs so that a < b
	_sortPairsVector();

	//2. sort pairs by the bigger number. unpaired element is ignored.
	if (_unorderedNumbers % 2 == 0)
		_sortByGreaterVector( _vector.begin() + _unorderedNumbers - 1);
	else
		_sortByGreaterVector(_vector.begin() + _unorderedNumbers - 2);

	//3. generate jacobsthal sequence
	_generateJacobsthal();

	//4. generete a sequence for inserting the unordered small numbers
	_generateInsertionSequence();

	//5. insert the small numbers using this sequence
	_insertSmallVector();
}
