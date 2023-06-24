#pragma once

#include <stack>
#include <string>

class RPN
{
private:
	std::string		_expression;
	std::stack<int>	_stack;

	void	_operate(char o);

public:
	RPN();
	RPN(std::string arg);
	RPN(const RPN& other);
	RPN&	operator=(const RPN& other);
	~RPN();

	bool	validOperator(char c);
	int		result();
};
