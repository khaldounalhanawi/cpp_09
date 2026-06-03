#include <iostream>
#include "RPN.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2 || argv[1][0] == '\0')
	{
		std::cerr << "Program needs 1 argument" << std::endl;
		return (1);
	}

	return (RPN (argv[1]));
}