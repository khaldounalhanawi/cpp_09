#include <iostream>
#include <sstream> 
#include <string>

bool	validateChar(const char c)
{
	const std::string allowed = "+-/*";

	if (allowed.find (c, 0) != std::string::npos
	|| (c >= '0' && c <= '9'))
		return (true);

	return (false);
}

int	main(int argc, char **argv)
{
	if (argc != 2 || argv[1][0] == '\0')
	{
		std::cerr << "Program needs 1 argument" << std::endl;
		return (1);
	}

	std::istringstream sstream (argv[1]);
	std::string token;
	bool emptyString = true;
	while (sstream >> token)
	{
		emptyString = false;
		if (token.size () != 1
			|| !validateChar (*token.c_str()))
		{
			std::cerr << "Error";
			return (2);
		}
		std::cout << token << "\n" ;
	}
	if (emptyString)
	{
		std::cerr << "Error";
		return (2);
	}
	// std::cout << validateChar (argv[1][0]) ;

	return (0);
}