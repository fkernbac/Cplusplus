#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <stdexcept>

void	insertionSort(std::vector<int>& arr, int start, int end)
{
	for (size_t i = start + 1; i <= end; i++)
	{
		int		value = arr[i];
		size_t	j = i;

		while (j > start && arr[j - 1] > value)
		{
			arr[j] = arr[j - 1];
			j--;
		}
		arr[j] = value;
	}
}

void	insertionSortList(std::list<int>& list, std::list<int>::iterator start, std::list<int>::iterator end)
{
	for (std::list<int>::iterator it = start; it != end; ++it)
	{
		typename std::list<int>::iterator	j = std::prev(it);

		while (j != start && *j > *it)
			j--;
		if (*j > *it)
			list.splice(j, list, prev(++it));
	}
std::cout << "insert sort: ";
for (std::list<int>::iterator it = start; it != end; it++)
	std::cout << *it << " ";
std::cout << "\n";
}

void	mergeSort(std::vector<int>& arr, int start, int mid, int end)
{
	std::vector<int>	temp(end - start + 1);
	int					first = start;
	int					second = mid + 1;
	int					i = 0;

	while (first <= mid && second <= end)
	{
		if (arr[first] < arr[second])
			temp[i] = arr[first++];
		else
			temp[i] = arr[second++];
		i++;
	}
	for (; first <= mid; first++)
		temp[i++] = arr[first];
	for (; second <= end; second++)
		temp[i++] = arr[second];

	std::copy(temp.begin(), temp.end(), arr.begin() + start);
}

void	mergeSortList(std::list<int>& list, std::list<int>::iterator start, std::list<int>::iterator mid, std::list<int>::iterator end)
{
	std::list<int>::iterator	first = start;
	std::list<int>::iterator	second = mid++;
	std::list<int>::iterator	it = start;

	while (first != second && second != end)
	{
		if (*first < *second)
			first++;
		else
			list.splice(first, list, std::prev(++second));
	}
}

void	mergeInsertionSortVector(std::vector<int>& arr, int start, int end, int threshold)
{
	if (start >= end)
		throw std::runtime_error("Error: wrong indices.");

	if (end - start + 1 <= threshold)
		insertionSort(arr, start, end);
	else
	{
		int	mid = (start + end) / 2;

		mergeInsertionSortVector(arr, start, mid, threshold);
		mergeInsertionSortVector(arr, mid + 1, end, threshold);
		mergeSort(arr, start, mid, end);
	}
}

void	mergeInsertionSortList(std::list<int>& lst, std::list<int>::iterator start, std::list<int>::iterator end, int threshold)
{
	int	distance = std::distance(start, end);
	if (distance <= threshold)
		insertionSortList(lst, start, end);
	else
	{
		std::list<int>::iterator	mid = start;
		std::advance(mid, distance / 2);

		mergeInsertionSortList(lst, start, mid, threshold);
		mergeInsertionSortList(lst, ++mid, end, threshold);
		mergeSortList(lst, start, mid, end);
	}
}

int	main()
{
	std::vector<int>	vector = {4, 14312, 1, 90, 3535, 45, 78, 3, 7657, 7647264, 5, 0, 6, 9, 657, 45, 89, 45573};
	std::list<int>		list(vector.begin(), vector.end());
	int					threshold = 10;

	clock_t	startTime = clock();
	mergeInsertionSortVector(vector, 0, vector.size() - 1, threshold);
	clock_t	endTime = clock();
	double	elapsedTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
	std::cout << "Vector sorted in " << elapsedTime << " ns\n";

	for (std::vector<int>::const_iterator it = vector.begin(); it != vector.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	startTime = clock();
	mergeInsertionSortList(list, list.begin(), list.end(), threshold);
	endTime = clock();
	endTime = static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC;
	std::cout << "List sorted in " << elapsedTime << " ns\n";

	for (std::list<int>::const_iterator it = list.begin(); it != list.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	return (0);
}