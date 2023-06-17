#ifndef PMERGEME_TPP
#define PMERGEME_TPP

#include <iostream>

/* SORTING ALGORITHM =========================================================*/

template<typename IteratorType>
void PmergeMe::_sortPairs(IteratorType begin, IteratorType end)
{
	for (IteratorType it = begin + 1; it != end; it += 2)
		if (*(it - 1) > *it)
			std::iter_swap(it - 1, it);
}

template<typename IteratorType>
void PmergeMe::_sortByGreater(IteratorType begin, IteratorType end, IteratorType startIt)
{
	if (startIt <= begin + 1)
		return;

	_sortByGreater(begin, end, startIt - 2);
	_insertPair(begin, end, startIt, startIt - 2);
}

template<typename IteratorType>
void PmergeMe::_insertPair(IteratorType begin, IteratorType end, IteratorType sortIt, IteratorType compareIt)
{
	if (compareIt == begin || *compareIt < *sortIt)
		std::iter_swap(sortIt - 1, sortIt);
	else
		_insertPair(begin, end, sortIt, compareIt - 2);
}

template<typename ContainerType>
void PmergeMe::_insertSmall(ContainerType& container)
{
	for (typename std::vector<int>::iterator it = _sortSequence.begin(); it != _sortSequence.end(); it++)
	{
		int containerIndex = *it + 1;
		if (containerIndex > _size - 1)
			continue;
std::cout << "segfault?" << std::endl;
		typename ContainerType::iterator eraseIt = container.begin() + containerIndex;
		int value = *eraseIt;
		container.erase(eraseIt);
std::cout << "no" << std::endl;
		_mergeInsert(container, value);
	}
}

template<typename ContainerType>
void PmergeMe::_mergeInsert(ContainerType& container, int value)
{
	typename ContainerType::iterator it = container.begin();
	while (value > *it && it != container.end())
		it++;

	container.insert(it, value);
}

#endif
