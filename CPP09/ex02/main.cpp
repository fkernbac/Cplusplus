#include "PmergeMe.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>

std::string	argsToString(int argc, char** argv)
{
	std::string	sequence;
	for (int i = 1; i < argc; i++)
	{
		sequence.append(argv[i]);
		sequence.append(" ");
	}
	return (sequence);
}

int	main(int argc, char** argv)
{
	if (argc < 2)
		return (1);

	try
	{
		std::string			sequence = argsToString(argc, argv);
		PmergeMe			sort(sequence);

		sort.printResult();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}

	return (0);
}
