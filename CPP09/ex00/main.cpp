#include "BitcoinExchange.hpp"
#include <iostream>
#include <stdexcept>

int	main(int argc, char** argv)
{
	BitcoinExchange	database;
	std::string		datafile("data.csv");

	if (argc != 2)
	{
		std::cerr << "Error: invalid arguments.\n";
		return (1);
	}

	try
	{
		database.readData(datafile);
		database.print(argv[1]);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what();
		return (1);
	}

	return (0);
}
