#include <iostream>
#include "types.hpp"
#include "buildDataBase.hpp"
#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	t_map	data;

	if (argc != 2)
	{
		std::cerr	<< "Error: could not open file." << std::endl;
		return (1);
	}
	try { buildDataBase (data, ',', "assets/data.csv", true); }
	catch (const std::runtime_error &e) { std::cerr << e.what(); return (1); }
	if (data.empty ())
	{
		std::cerr	<< "Data base is empty!" << std::endl;
		return (2);
	}
	BitcoinExchange (data, argv[1], '|');
	return (0);
}
