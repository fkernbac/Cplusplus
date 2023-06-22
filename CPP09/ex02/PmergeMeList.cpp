#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>


/* LIST SORTING ALGORITHM =========================================================*/

void	PmergeMe::_makePairsList()
{
	// Iterate over the numbers vector, incrementing the iterator by 2 each time
	for (std::vector<int>::const_iterator it = _unsortedVector.begin(); it != _unsortedVector.end(); std::advance(it, 2))
	{
		// Check if there are at least two elements remaining
		if (it == --_unsortedVector.end())
			return;
		// Create a pair from the current and next elements
		std::pair<int, int> pair(*it, *(it + 1));

		// Add the pair to the pairs vector
		_pairList.push_back(pair);
	}
}

void	PmergeMe::_sortPairsList()
{
	for (std::list<std::pair<int, int> >::iterator it = _pairList.begin(); it != _pairList.end(); it++)
	{
		if (it->first > it->second)
			std::swap(it->first, it->second);
	}
}

struct PairSecondComparator {
	bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs)
	{
		return lhs.second < rhs.second;
	}
};

void	PmergeMe::_sortByGreaterList()
{
	// PairSecondComparator	comparator;
	// _pairList.sort(comparator);
	// std::sort(_pairList.begin(), _pairList.end(), comparePairs);
	_pairList.sort(comparePairs);
	// for (std::list<std::pair<int, int> >::iterator it = _pairList.begin(); it != _pairList.end(); it++)
	// 	_binaryInsertList(it);
}

void	PmergeMe::_mainChainList()
{
	std::pair<int, int>	firstElement = std::make_pair(-1, _pairList.begin()->first);

	_pairList.begin()->first = -1;
	_pairList.insert(_pairList.begin(), firstElement);
}

void	PmergeMe::_insertSmallList()
{
	int	insertedElements = 0;

	for (std::vector<int>::iterator it = _jacobsthal.begin(); it != _jacobsthal.end(); it++)
	{
		std::list<std::pair<int, int> >::iterator groupIt = _pairList.begin();
		std::advance(groupIt, *it + insertedElements);

		//insert each element before this element
		int	insertedGroupElements = 0;
		while (1)
		{
			//find first small element that needs to be sorted
			for (; groupIt != _pairList.begin(); groupIt--)
				if (groupIt->first != -1)
					break;
			//check if all elements are sorted
			if (groupIt == _pairList.begin())
				break;

			//create the new element
			std::pair<int, int>	newPair = std::make_pair(-1, groupIt->first);
			//remove element from original place
			groupIt->first = -1;
			//insert element in the main chain
			groupIt = _pairList.insert(groupIt, newPair);

			//sort all elements including this one
			_binaryInsertList(groupIt);
			insertedElements++;
			insertedGroupElements++;

			groupIt = _pairList.begin();
			std::advance(groupIt,  *it + insertedElements - insertedGroupElements);
		}
	}
	if (_unsortedVector.size() % 2 != 0)
	{
		std::pair<int, int>	odd = std::make_pair(-1, _unsortedVector.back());

		_pairList.push_back(odd);
		_pairList.sort(comparePairs);
	}
}

void	PmergeMe::_binaryInsertList(std::list<std::pair<int, int> >::iterator sortIt)
{
	std::list<std::pair<int, int> >	unorderedList;
	//cut list in ordered and unordered half
	unorderedList.splice(unorderedList.begin(), _pairList, ++sortIt, _pairList.end());
	//binary sort ordered half
	_pairList.sort(comparePairs);
	//merge lists back together
	_pairList.splice(_pairList.end(), unorderedList);
}

void	PmergeMe::_sortList()
{
	_makePairsList();

	//1. sort pairs so that a < b
	_sortPairsList();

	//2. sort pairs by the bigger number. unpaired element is ignored.
	_sortByGreaterList();

	_mainChainList();

	//3. generate jacobsthal sequence
	_generateJacobsthal();

	//5. insert the small numbers using this sequence
	_insertSmallList();
}
