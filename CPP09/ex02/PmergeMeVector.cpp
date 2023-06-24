#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>


/* VECTOR SORTING ALGORITHM =========================================================*/

void	PmergeMe::_makePairsVector()
{
	// Iterate over the numbers vector, incrementing the iterator by 2 each time
	for (std::vector<int>::const_iterator it = _unsorted.begin(); it != _unsorted.end(); std::advance(it, 2))
	{
		// Check if there are at least two elements remaining
		if (it == --_unsorted.end())
			return;
		// Create a pair from the current and next elements
		std::pair<int, int> pair(*it, *(it + 1));

		// Add the pair to the pairs vector
		_pairVector.push_back(pair);
	}
}

void	PmergeMe::_sortPairsVector()
{
	for (std::vector<std::pair<int, int> >::iterator it = _pairVector.begin(); it != _pairVector.end(); it++)
	{
		if (it->first > it->second)
			std::swap(it->first, it->second);
	}
}

void	PmergeMe::_sortByGreaterVector()
{
	std::sort(_pairVector.begin(), _pairVector.end(), comparePairs);
}

void	PmergeMe::_mainChainVector()
{
	std::pair<int, int> firstElement = std::make_pair(-1, _pairVector[0].first);

	_pairVector[0].first = -1;
	_pairVector.insert(_pairVector.begin(), firstElement);
}

void	PmergeMe::_insertSmallVector()
{
	int	insertedElements = 0;
	int	groupSize = 2;

	//iterate to first element of group
	for (unsigned int i = 0; i < _jacobsthal.size(); i++)
	{
		int	insertedGroupElements = 0;
		if (i > 0)
			groupSize = _jacobsthal[i] - _jacobsthal[i - 1];

		//insert each element before this element
		while (insertedGroupElements < groupSize)
		{
			std::vector<std::pair<int, int> >::iterator groupIt = _pairVector.begin() + _jacobsthal[i] + insertedElements - insertedGroupElements;
			//search first element that hasn't been inserted yet
			while (groupIt->first == -1 && groupIt != _pairVector.begin())
				groupIt--;
			if (groupIt <= _pairVector.begin())
				break;

			std::pair<int, int>	element = std::make_pair(-1, groupIt->first);

			groupIt->first = -1;
			groupIt--;

			_binaryInsertVector(element, groupIt);

			insertedElements++;
			insertedGroupElements++;
		}
	}
	//if there is an odd element, insert it
	if (_unsorted.size() % 2 != 0)
		_binaryInsertVector(std::make_pair(-1, _unsorted.back()), _pairVector.end());
}

void	PmergeMe::_binaryInsertVector(std::pair<int, int> element, std::vector<std::pair<int, int> >::iterator last)
{
	std::vector<std::pair<int, int> >::iterator first = _pairVector.begin();

	while (first != last)
	{
		std::vector<std::pair<int, int> >::iterator	mid = first + std::distance(first, last) / 2;

		if (element.second < mid->second)
			last = mid;
		else
			first = mid + 1;
	}

	_pairVector.insert(first, element);
}

void	PmergeMe::_sortVector()
{
	// clock_t	startTime;
	// clock_t	endTime;
	// double	time;

	_makePairsVector();

	//1. sort pairs so that a < b
	// startTime = clock();
	_sortPairsVector();

	// endTime = clock();
	// time = static_cast<double>(endTime - startTime);
	// std::cout << "_sortPairsVector(): " << time << "\n";

	//2. sort pairs by the bigger number. unpaired element is ignored.
	// startTime = clock();

	_sortByGreaterVector();

	// endTime = clock();
	// time = static_cast<double>(endTime - startTime);
	// std::cout << "_sortByGreaterVector(): " << time << "\n";

	//3. set up sorted part
	_mainChainVector();

	//4. generate jacobsthal sequence
	_generateJacobsthal();

	//5. insert the small numbers using this sequence
	// startTime = clock();
	_insertSmallVector();

	// endTime = clock();
	// time = static_cast<double>(endTime - startTime);
	// std::cout << "__insertSmallVector(): " << time << "\n";
}
