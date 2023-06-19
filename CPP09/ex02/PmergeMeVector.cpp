#include "PmergeMe.hpp"
#include <iostream>


/* VECTOR SORTING ALGORITHM =========================================================*/

void	PmergeMe::_sortPairsVector()
{
	for (std::vector<int>::iterator it = _unsortedVector.begin() + 1; it < _unsortedVector.end(); it += 2)
	{
		_comparisons++;
		if (*(it - 1) > *it)
			std::iter_swap(it - 1, it);
	}
}

/*Recursive function for inserting at the front.*/
void	PmergeMe::_sortByGreaterVector(std::vector<int>::iterator startIt)
{
	if (startIt <= _unsortedVector.begin() + 1)
		return;

	_sortByGreaterVector(startIt - 2);
	_insertPairVector(startIt, startIt - 2);
}

/*Recursive function for finding the right spot for insertion.*/
void	PmergeMe::_insertPairVector(std::vector<int>::iterator sortIt, std::vector<int>::iterator compareIt)
{
		_comparisons++;
std::cout << *compareIt << " < " << *sortIt << "?\n";
	if (*compareIt < *sortIt)
	{
		int	bigger = *sortIt;
		int	smaller = *--sortIt;

		compareIt++;

		sortIt = _unsortedVector.erase(sortIt);
		_unsortedVector.erase(sortIt);

		_unsortedVector.insert(compareIt, bigger);
		_unsortedVector.insert(compareIt, smaller);
	}
	else if (compareIt == _unsortedVector.begin())
	{
		int	bigger = *sortIt;
		int	smaller = *--sortIt;

		sortIt = _unsortedVector.erase(sortIt);
		_unsortedVector.erase(sortIt);

		_unsortedVector.push_back(bigger);
		_unsortedVector.push_back(smaller);
	}
	else
		_insertPairVector(sortIt, compareIt - 2);
}

void	PmergeMe::_mainChainVector(std::vector<int>::iterator endIt)
{
	for (; endIt != _unsortedVector.begin(); endIt--)
	{
		_sortedVector.insert(_sortedVector.begin(), *endIt);
		endIt = _unsortedVector.erase(endIt);
		endIt--;
		if (endIt == _unsortedVector.begin())
			break;
	}
	_sortedVector.insert(_sortedVector.begin(), *endIt);
	_unsortedVector.erase(endIt);
}

void	PmergeMe::_insertSmallVector()
{
	for(std::vector<int>::iterator	it = _insertionSequence.begin(); it != _insertionSequence.end(); it++)
	{
		if ((unsigned long) *it > _unsortedVector.size() - 1)
			continue;

		for (std::vector<int>::iterator orderedIt = _sortedVector.begin(); orderedIt != _sortedVector.end(); orderedIt++)
		{
			_comparisons++;
std::cout << *orderedIt << " < " << _unsortedVector[*it] << "?\n";
			if (*orderedIt >= _unsortedVector[*it])
			{
				_sortedVector.insert(orderedIt, _unsortedVector[*it]);
				break;
			}
		}
	}
}

void	PmergeMe::_sortVector()
{
	_comparisons = 0;

	//1. sort pairs so that a < b
	_sortPairsVector();
std::cout << "comparisons after pair sorting: " << _comparisons << std::endl;
	//2. sort pairs by the bigger number. unpaired element is ignored.
	std::vector<int>::iterator	lastIndex = --_unsortedVector.end();
	if (_unsortedVector.size() % 2 != 0)
		lastIndex--;
printVector();
	_sortByGreaterVector(lastIndex);
std::cout << "comparisons after sorting by greater element: " << _comparisons << std::endl;
	_mainChainVector(lastIndex);

	//3. generate jacobsthal sequence
	_generateJacobsthal();

	//4. generete a sequence for inserting the unordered small numbers
	_generateInsertionSequence();

	//5. insert the small numbers using this sequence
	_insertSmallVector();

	std::cout << "comparisons needed: " << _comparisons << "\n";
}
