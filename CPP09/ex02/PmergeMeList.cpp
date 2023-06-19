#include "PmergeMe.hpp"
#include <iostream>


/* LIST SORTING ALGORITHM =========================================================*/

void	PmergeMe::_sortPairsList()
{
	for (std::list<int>::iterator it = _unsortedList.begin(); it != _unsortedList.end(); it++)
	{
		//iterator at first element
		std::list<int>::iterator	second = it;
		second++;
		//need to check if we exceeded the list
		if (second == _unsortedList.end())
			return;

		_comparisons++;
		if (*it > *second)
			std::iter_swap(it, second);

		//need to increment a second time to reach smaller element
		it++;
	}
}

/*Recursive function for inserting at the front.*/
void	PmergeMe::_sortByGreaterList(std::list<int>::iterator startIt)
{
	if (startIt == ++_unsortedList.begin())
		return;

	std::list<int>::iterator	nextPair = startIt;
	nextPair--;
	nextPair--;
	_sortByGreaterList(nextPair);

	nextPair = startIt;
	nextPair--;
	nextPair--;

	_insertPairList(startIt, nextPair);
}

void	PmergeMe::_insertPairList(std::list<int>::iterator sortIt, std::list<int>::iterator compareIt)
{
	std::list<int>::iterator	smallElement = sortIt;
	smallElement--;

	_comparisons++;
	if (*compareIt < *sortIt)
	{
		//increment because we need to insert after the smaller element
		compareIt++;

		//no need to insert an element if it is already the biggest one
		if (compareIt == smallElement)
			return;

		_unsortedList.splice(compareIt, _unsortedList, smallElement, ++sortIt);
	}
	else if (compareIt == ++_unsortedList.begin())
		_unsortedList.splice(_unsortedList.begin(), _unsortedList, smallElement, ++sortIt);
	else
	{
		compareIt--;
		compareIt--;
		_insertPairList(sortIt, compareIt);
	}
}

void	PmergeMe::_mainChainList()
{
	std::list<int>::iterator	it = ++_unsortedList.begin();
	it++;
	_sortedList.splice(_sortedList.begin(), _unsortedList, _unsortedList.begin(), it);

	it = ++_unsortedList.begin();
	while (it != _unsortedList.end())
	{
		std::list<int>::iterator	moveIt = it;
		it++;
		_sortedList.splice(_sortedList.end(), _unsortedList, moveIt);

		//check if there is an odd element at the end of the list
		if (++it == _unsortedList.end())
			return;
	}
}

void	PmergeMe::_insertSmallList()
{
	for (std::vector<int>::iterator it = _insertionSequence.begin(); it != _insertionSequence.end(); it++)
	{
		std::list<int>::iterator	listIt = _unsortedList.begin();
		std::advance(listIt, *it);

		//check if index is too big
		if ((unsigned long) *it > _unsortedList.size() - 1)
			continue;

		//insert value into ordered list
		for (std::list<int>::iterator orderedIt = _sortedList.begin(); orderedIt != _sortedList.end(); orderedIt++)
		{
			_comparisons++;
			if (*orderedIt >= *listIt)
			{
				_sortedList.insert(orderedIt, *listIt);
				break;
			}
		}
	}
}

void	PmergeMe::_sortList()
{
	_comparisons = 0;

	//1. sort pairs so that a < b
	_sortPairsList();
std::cout << "comparisons after pair sorting: " << _comparisons << std::endl;
	//2. sort pairs by the bigger number. unpaired element is ignored.
	std::list<int>::iterator	last = --_unsortedList.end();
	if (_unsortedList.size() % 2 != 0)
		last--;

	_sortByGreaterList(last);
std::cout << "comparisons after sorting by greater element: " << _comparisons << std::endl;
	_mainChainList();

	//3. generate jacobsthal sequence
	_generateJacobsthal();

	//4. generete a sequence for inserting the unordered small numbers
	_generateInsertionSequence();

	//5. insert the small numbers using this sequence
	_insertSmallList();

	std::cout << "comparisons needed: " << _comparisons << "\n";
}
