#include <vector>
#include <list>
#include <string>

class PmergeMe
{
private:
	std::vector<int>	_unsortedVector;
	std::vector<int>	_sortedVector;

	std::list<int>		_unsortedList;
	std::list<int>		_sortedList;

	std::vector<int>	_jacobsthal;
	std::vector<int>	_insertionSequence;

	unsigned int		_comparisons;

	void	_sortVector();
	void	_sortPairsVector();
	void	_sortByGreaterVector(std::vector<int>::iterator startIt);
	void	_insertPairVector(std::vector<int>::iterator sortIt, std::vector<int>::iterator compareIt);
	void	_mainChainVector(std::vector<int>::iterator endIt);
	void	_insertSmallVector();
	void	_binaryInsertVector(int value);

	void	_sortList();
	void	_sortPairsList();
	void	_sortByGreaterList(std::list<int>::iterator startIt);
	void	_insertPairList(std::list<int>::iterator sortIt, std::list<int>::iterator compareIt);
	void	_mainChainList();
	void	_insertSmallList();

	void	_generateInsertionSequence();
	void	_generateJacobsthal();

public:
	PmergeMe();
	PmergeMe(std::string& sequence);
	PmergeMe(const PmergeMe& other);
	PmergeMe&	operator=(const PmergeMe& other);
	~PmergeMe();

	void	printVector();
	void	printSortedVector();
	void	printList();
	void	printSortedList();
	void	printResult();
};
