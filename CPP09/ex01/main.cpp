#include "RPN.hpp"
#include <iostream>
#include <stdexcept>

int	main(int argc, char** argv)
{
	if (argc != 2 || !argv[1])
	{
		std::cerr << "Error: invalid arguments.\n";
		return (1);
	}

	try
	{
		RPN	calculation(argv[1]);
		std::cout << calculation.result() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}

	return (0);
}
