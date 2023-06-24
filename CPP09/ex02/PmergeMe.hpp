#pragma once

#include <vector>
#include <list>
#include <string>

class PmergeMe
{
private:
/* CONTAINERS ================================================================*/
	std::vector<std::pair<int, int> >	_pairVector;
	std::list<std::pair<int, int> >		_pairList;

	std::vector<int>	_unsorted;
	std::vector<int>	_jacobsthal;

/* SORTING ALGORITHM =========================================================*/
	void	_sortVector();
	void	_makePairsVector();
	void	_sortPairsVector();
	void	_sortByGreaterVector();
	void	_mainChainVector();
	void	_insertSmallVector();
	void	_binaryInsertVector(std::pair<int, int> element, std::vector<std::pair<int, int> >::iterator last);

	void	_sortList();
	void	_makePairsList();
	void	_sortPairsList();
	void	_sortByGreaterList();
	void	_mainChainList();
	void	_insertSmallList();
	void	_binaryInsertList(std::pair<int, int> element, std::list<std::pair<int, int> >::iterator last);

	void	_generateJacobsthal();

public:
/* CONSTRUCTORS ==============================================================*/
	PmergeMe();
	PmergeMe(std::string& sequence);
	PmergeMe(const PmergeMe& other);
	PmergeMe&	operator=(const PmergeMe& other);
	~PmergeMe();

/* FUNCTIONS =================================================================*/
	void	printUnsorted();
	void	printVector();
	void	printPairVector();

	void	printList();
	void	printPairList();

	void	printResult();

	static bool	comparePairs(const std::pair<int, int>& a, const std::pair<int, int>& b);
};
