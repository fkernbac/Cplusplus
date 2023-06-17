#include <vector>
#include <list>
#include <string>

class PmergeMe
{
private:
	int					_unorderedNumbers;
	std::vector<int>	_vector;
	std::vector<int>	_jacobsthal;
	std::vector<int>	_insertionSequence;
	std::list<int>		_unsortedList;
	std::list<int>		_sortedList;

	void	_sortVector();
	void	_sortPairsVector();
	void	_sortByGreaterVector(std::vector<int>::iterator startIt);
	void	_insertPairVector(std::vector<int>::iterator sortIt, std::vector<int>::iterator compareIt);
	void	_insertSmallVector();
	void	_mergeInsertVector(int value);

	void	_sortList();
	void	_sortPairsList();
	void	_sortGreaterList(std::list<int>::iterator startIt);
	void	_insertToOrdered(std::list<int>::iterator sortIt, std::list<int>::iterator compareIt);
	void	_insertSmallList();
	void	_mergeInsertList(int value);

	void	_generateInsertionSequence();
	void	_generateJacobsthal();

public:
	PmergeMe();
	PmergeMe(std::string& sequence);
	PmergeMe(const PmergeMe& other);
	PmergeMe&	operator=(const PmergeMe& other);
	~PmergeMe();

	void	printVector();
	void	printList();
	void	printSortedList();
	void	printResult();
};
