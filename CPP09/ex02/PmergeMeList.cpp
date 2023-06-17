#include "PmergeMe.hpp"
#include <iostream>


/* VECTOR SORTING ALGORITHM =========================================================*/

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

		if (*it > *second)
			std::iter_swap(it, second);

		//need to increment a second time to reach smaller element
		it++;
	}
}

/*Recursive function for inserting at the front.*/
void	PmergeMe::_sortGreaterList(std::list<int>::iterator startIt)
{
	if (startIt == ++_unsortedList.begin())
	{
		_sortedList.push_back(*_unsortedList.begin());
		_sortedList.push_back(*startIt);

		_unsortedList.erase(_unsortedList.begin());
		_unsortedList.erase(_unsortedList.begin());

		return;
	}

	std::list<int>::iterator	nextPair = startIt;
	nextPair--;
	nextPair--;

	_sortGreaterList(nextPair);
	_insertToOrdered(startIt, --_sortedList.end());
}

/*Recursive function for finding the right spot for insertion.*/
void	PmergeMe::_insertToOrdered(std::list<int>::iterator sortIt, std::list<int>::iterator compareIt)
{
	if (*compareIt < *sortIt)
	{
		_sortedList.insert(++compareIt, *sortIt);
		_unsortedList.erase(sortIt);
	}
	else if (compareIt == _sortedList.begin())
	{
		_sortedList.push_front(*sortIt);
		_unsortedList.erase(sortIt);
	}
	else
		_insertToOrdered(sortIt, --compareIt);
}

void	PmergeMe::_insertSmallList()
{
	for (std::vector<int>::iterator it = _insertionSequence.begin(); it != _insertionSequence.end(); it++)
	{
		std::list<int>::iterator	listIt = _unsortedList.begin();
		std::advance(listIt, *it);

		if (*it < _unorderedNumbers)
		{
			std::list<int>::iterator	orderedIt = _sortedList.begin();

			while (*listIt > *orderedIt)
				orderedIt++;
			_sortedList.insert(orderedIt, *listIt);
		}
	}
}

void	PmergeMe::_mergeInsertList(int value)
{
	std::list<int>::iterator	it = _unsortedList.begin();
	while (value > *it && it != _unsortedList.end())
		it++;

	_unsortedList.insert(it, value);
}

void	PmergeMe::_sortList()
{
printList();
	//1. sort pairs so that a < b
	_sortPairsList();
printList();
	//2. sort pairs by the bigger number. unpaired element is ignored.
	std::list<int>::iterator	last = --_unsortedList.end();
	if (_unorderedNumbers % 2 != 0)
		last--;
	_sortGreaterList(last);
printSortedList();
printList();
	//3. generate jacobsthal sequence
	_unorderedNumbers = _unsortedList.size();
	_generateJacobsthal();

for (std::vector<int>::iterator it = _jacobsthal.begin(); it != _jacobsthal.end(); it++)
	std::cout << *it << " ";
std::cout << std::endl;

	//4. generete a sequence for inserting the unordered small numbers
	_generateInsertionSequence();

for (std::vector<int>::iterator it = _insertionSequence.begin(); it != _insertionSequence.end(); it++)
	std::cout << *it << " ";
std::cout << std::endl;


std::cout << "insert small numbers" << std::endl;
	//5. insert the small numbers using this sequence
	_insertSmallList();

printList();
printSortedList();
}
