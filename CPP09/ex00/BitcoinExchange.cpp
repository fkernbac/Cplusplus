#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdexcept>
#include <cerrno>

/* CONSTRUCTORS ==============================================================*/
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	std::map<std::string, double>::const_iterator	it;
	for (it = other._data.begin(); it != other._data.end(); it++)
		_data.insert(std::make_pair(it->first, it->second));
}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		std::map<std::string, double>::const_iterator	it;
		for (it = other._data.begin(); it != other._data.end(); it++)
			_data.insert(std::make_pair(it->first, it->second));
	}

	return (*this);
}

BitcoinExchange::~BitcoinExchange() {}

/* FUNCTIONS =================================================================*/

void	BitcoinExchange::readData(const std::string& filename)
{
	std::ifstream	file(filename.c_str());
	if (!file)
	{
		throw std::runtime_error("Error: database could not be opened.");
	}

	std::string	line;
	while (std::getline(file, line))
	{
		std::string	key = line.substr(0, 10);
		double		value = std::strtod(line.c_str() + 11, NULL);

		_data[key] = value;
	}
}

std::string	BitcoinExchange::_convertDate(const std::string& date)
{
	if (date.length() < 10)
		throw std::runtime_error("Error: bad input -> " + date);
	if (date[4] != '-' || date[7] != '-')
		throw std::runtime_error("Error: invalid date format.");

	return (date.substr(0, 10));
}

float	BitcoinExchange::_convertAmount(const std::string& s)
{
	if (s.empty())
		throw std::runtime_error("Error: bad input.");
	if (s.length() > 4)
		throw std::runtime_error("Error: too large a number.");

	const char*	c = s.c_str();
	char*		endptr;
	float		amount = std::strtof(c, &endptr);

	if (c == endptr)
		throw std::runtime_error("Error: not a valid integer.");
	if (*endptr != '\0')
		throw std::runtime_error("Error: bad input => " + s);
	if (amount < 0)
		throw std::runtime_error("Error: not a positive number.");
	if (amount > 1000)
		throw std::runtime_error("Error: too large a number.");

	return (amount);
}

float	BitcoinExchange::_getPrice(std::string& date, float amount)
{
	std::map<std::string, double>::iterator	it = _data.upper_bound(date);
	it--;

	return (amount * it->second);
}

void	BitcoinExchange::print(const std::string& filename)
{
	std::ifstream	file(filename.c_str());
	std::string		line;

	if (!file)
		throw std::runtime_error("Error: file could not be opened.");

	while (std::getline(file, line))
	{
		if (line.length() < 14)
			std::cerr << "Error: bad input => " << line;
		else
		{
			try {
				std::string	date = _convertDate(line);
				float		amount = _convertAmount(line.substr(13, std::string::npos));
				float		price = _getPrice(date, amount);

				std::cout << date << " => " << amount << " = " << price;
			}
			catch (const std::exception& e)
			{
				std::cout << e.what();
			}
		}
		std::cout << "\n";
	}
}
