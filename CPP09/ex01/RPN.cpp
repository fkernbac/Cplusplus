#include "RPN.hpp"
#include <cctype>
#include <stdexcept>
#include <iostream>

/* CONSTRUCTORS ==============================================================*/
RPN::RPN() {}

RPN::RPN(std::string arg) : _expression(arg) {}

RPN::RPN(const RPN& other) : _expression(other._expression) {}

RPN&	RPN::operator=(const RPN& other)
{
	if (this != &other)
		_expression = other._expression;

	return (*this);
}

RPN::~RPN() {}

/* FUNCTIONS =================================================================*/

void	RPN::_operate(char o)
{
	if (_stack.empty())
		throw std::runtime_error("Error: missing operands.");
	int	right = _stack.top();
	_stack.pop();

	if (_stack.empty())
		throw std::runtime_error("Error: missing operands.");
	int	left = _stack.top();
	_stack.pop();

// std::cout << left << " " << o << " " << right << std::endl;

	int	result;
	switch (o)
	{
	case '+':
		result = left + right;
		break;
	case '-':
		result = left - right;
		break;
	case '*':
		result = left * right;
		break;
	case '/':
		if (right == 0)
			throw std::runtime_error("Error: division by 0.");
		result = left / right;
		break;
	}
// std::cout << "pushing back" << std::endl;
	_stack.push(result);
}

bool	RPN::validOperator(char c)
{
	if (c == '+' || c == '-' || c == '/' || c == '*')
		return (true);
	return (false);
}

int	RPN::result()
{
	if (_expression.empty())
		throw std::runtime_error("Error: empty expression.");

	for (std::string::size_type i = 0; i < _expression.length(); i++)
	{
		if (std::isdigit(_expression[i]))
			_stack.push(_expression[i] - '0');
		else if (validOperator(_expression[i]) == true)
			_operate(_expression[i]);
		else if (std::isspace(_expression[i]) == false)
			throw std::runtime_error("Error: invalid character.");
	}

	int	result = _stack.top();
	_stack.pop();
	if (_stack.empty() == false)
		throw std::runtime_error("Error: missing operators.");

	return (result);
}
