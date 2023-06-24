#pragma once

#include <map>
#include <list>
#include <string>

class BitcoinExchange
{
private:
	std::map<std::string, double>	_data;
	std::list<std::string>			_dates;

	std::string	_convertDate(const std::string& date);
	float		_convertAmount(const std::string& value);
	float		_getPrice(std::string& date, float amount);

public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange&	operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	void	readData(const std::string& filename);
	void	print(const std::string& filename);
};
