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

void	PmergeMe::insertVector(std::vector<int>& arr, int start, int end)
{
	for (int i = start + 1; i <= end; i++)
	{
		int		value = arr[i];
		int	j = i;

		while (j > start && arr[j - 1] > value)
		{
			arr[j] = arr[j - 1];
			j--;
		}
		arr[j] = value;
	}
}

void	PmergeMe::mergeVector(std::vector<int>& arr, int start, int mid, int end)
{
	std::vector<int>	temp(end - start + 1);
	int					first = start;
	int					second = mid + 1;

	int	i = 0;
	while (first <= mid && second <= end)
	{
		if (arr[first] < arr[second])
			temp[i] = arr[first++];
		else
			temp[i] = arr[second++];
		i++;
	}

	for(; first <= mid; first++)
		temp[i++] = arr[first];
	for(; second <= end; second++)
		temp[i++] = arr[second];

	std::copy(temp.begin(), temp.end(), arr.begin() + start);
}

void	PmergeMe::sortVector(std::vector<int>& arr, int start, int end, int threshold)
{
	if (end - start + 1 <= threshold)
		insertVector(arr, start, end);
	else
	{
		int	mid = (start + end) / 2;

		sortVector(arr, start, mid, threshold);
		sortVector(arr, mid + 1, end, threshold);
		mergeVector(arr, start, mid, end);
	}
}

void	PmergeMe::printResult()
{
	clock_t	startTime = clock();

	sortVector(_vector, 0, _unorderedNumbers - 1, _threshold);

	clock_t	endTime = clock();
	double	elapsedTime = static_cast<double>(endTime - startTime);

	std::cout << "Vector sorted in " << elapsedTime << " \n";

	for (std::vector<int>::const_iterator it = _vector.begin(); it != _vector.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
}
