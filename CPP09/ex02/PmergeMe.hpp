#include <vector>
#include <list>
#include <string>

class PmergeMe
{
private:
	std::vector<int>	_unsortedVector;

	std::vector<std::pair<int, int> >	_pairVector;
	std::list<std::pair<int, int> >		_pairList;

	std::vector<int>	_jacobsthal;

	void	_sortVector();
	void	_makePairsVector();
	void	_sortPairsVector();
	void	_sortByGreaterVector();
	void	_mainChainVector();
	void	_insertSmallVector();
	void	_binaryInsertVector(std::pair<int, int> insertElement, std::vector<std::pair<int, int> >::iterator first, std::vector<std::pair<int, int> >::iterator last);

	void	_sortList();
	void	_makePairsList();
	void	_sortPairsList();
	void	_sortByGreaterList();
	void	_mainChainList();
	void	_insertSmallList();
	void	_binaryInsertList(std::list<std::pair<int, int> >::iterator sortIt);

	void	_generateJacobsthal();

public:
	PmergeMe();
	PmergeMe(std::string& sequence);
	PmergeMe(const PmergeMe& other);
	PmergeMe&	operator=(const PmergeMe& other);
	~PmergeMe();

	void	printUnsorted();
	void	printVector();
	void	printPairVector();
	void	printList();
	void	printPairList();
	void	printResult();

	static bool	comparePairs(const std::pair<int, int>& a, const std::pair<int, int>& b);
};
