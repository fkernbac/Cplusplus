#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>


/* VECTOR SORTING ALGORITHM =========================================================*/

void	PmergeMe::_makePairsVector()
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

	//iterate to first element of group
	for (std::vector<int>::iterator it = _jacobsthal.begin(); it != _jacobsthal.end(); it++)
	{
		std::vector<std::pair<int, int> >::iterator groupIt = _pairVector.begin() + *it + insertedElements;

		//insert each element before this element
		int	insertedGroupElements = 0;
		while (1)
		{
			for (; groupIt >= _pairVector.begin(); groupIt--)
				if (groupIt->first != -1)
					break;
			if (groupIt <= _pairVector.begin())
				break;

			std::pair<int, int>	insertElement = std::make_pair(-1, groupIt->first);

			groupIt->first = -1;

			_binaryInsertVector(insertElement, _pairVector.begin(), groupIt);	//insertIt is the last element that is possibly smaller than what I'm inserting
			insertedElements++;
			insertedGroupElements++;

			groupIt = _pairVector.begin() + *it + insertedElements - insertedGroupElements;
		}
	}
	//if there is an odd element, insert it
	if (_unsortedVector.size() % 2 != 0)
	{
		std::pair<int, int>	odd = std::make_pair(-1, _unsortedVector.back());

		_binaryInsertVector(odd, _pairVector.begin(), _pairVector.end());
	}
}

void	PmergeMe::_binaryInsertVector(std::pair<int, int> insertElement, std::vector<std::pair<int, int> >::iterator first, std::vector<std::pair<int, int> >::iterator last)
{
	while (first != last)
	{
		std::vector<std::pair<int, int> >::iterator	mid = first + std::distance(first, last) / 2;

		if (insertElement.second < mid->second)
			last = mid;
		else
			first = mid + 1;
	}
	_pairVector.insert(first, insertElement);
}

void	PmergeMe::_sortVector()
{
	clock_t	startTime;
	clock_t	endTime;
	double	time;

	_makePairsVector();

	//1. sort pairs so that a < b
	startTime = clock();

	_sortPairsVector();

	endTime = clock();
	time = static_cast<double>(endTime - startTime);
	std::cout << "_sortPairsVector(): " << time << "\n";

	//2. sort pairs by the bigger number. unpaired element is ignored.
	startTime = clock();

	_sortByGreaterVector();

	endTime = clock();
	time = static_cast<double>(endTime - startTime);
	std::cout << "_sortByGreaterVector(): " << time << "\n";

	//3. set up sorted part
	_mainChainVector();

	//4. generate jacobsthal sequence
	_generateJacobsthal();

	//5. insert the small numbers using this sequence
	startTime = clock();

	_insertSmallVector();

	endTime = clock();
	time = static_cast<double>(endTime - startTime);
	std::cout << "__insertSmallVector(): " << time << "\n";
}
