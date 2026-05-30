#include <iostream>
#include <limits>
#include <iomanip>
#include <string>
#include "buildDataBase.hpp"
#include "types.hpp"
#include "stringManipulation.hpp"
#include "validateDate.hpp"


#include <fstream>

int	main(int argc, char **argv)
{
	t_map	data;

	// check input
	if (argc != 2)
	{
		std::cerr<< "Error: could not open file." << std::endl;
		return (1);
	}

	// build database
	try { buildDataBase (data, ',', "assets/data.csv", true); }
	catch (const std::runtime_error &e) { std::cerr << e.what(); return (1); }

	if (data.empty ())
	{
		std::cerr<< "Data base is empty!" << std::endl;
		return (2);
	}

	// parse input
	std::ifstream file(argv[1]);
	if (!file)
		throw std::runtime_error ("Error: could not open file.");

	// skip header
	std::string temp;
	std::getline(file, temp);

	char delimiter = '|';
	while (std::getline (file, temp))
	{
		// skip if line is empty
		if (temp.empty())
			continue;

		// split line into a pair of strings
		t_pairStr cell;
		if (!splitStr (temp, delimiter, cell))
		{
			std::cout << "bad input => " << temp << "\n";
			continue;
		}

		trimStr(cell.first);
		trimStr(cell.second);

		// validate the date
		if (!validateDate (cell.first))
		{
			std::cout << "bad input => " << cell.first << "\n";
			continue;
		}

		// convert value to double
		char *end = nullptr;
		double valueDouble = std::strtod (cell.second.c_str(), &end);

		if (end == cell.second.c_str() || *end != '\0')
		{
			std::cout << "bad input => " << cell.second << "\n";
			continue;
		}
		else if (valueDouble < 0)
		{
			std::cout << "Error: not a positive number." << "\n";
			continue;
		}
		else if (valueDouble > INT_MAX)
		{
			std::cout << "Error: too large a number." << "\n";
			continue;
		}

		// get closest lower bound
		t_map::iterator item = data.lower_bound (cell.first);
		if (item == data.end())
		{
			std::cout << "no find." << "\n"; // look closer
			continue;
		}
		else if ((*item).first != cell.first && item != data.begin()) // checks mate
		{
			-- item;
		}
		// print out
		std::cout	<< cell.first
					<< " => "
					<< cell.second
					<< " = "
					<< std::setprecision(15)
					<< valueDouble * data [(*item).first]
					<< "\n";
	}
	return (0);
}

/*
	for (t_map::iterator i  = data.begin(); i != data.end(); ++i)
		std::cout << i->first << "   ===   " << std::setprecision(15) << i->second << "\n";
*/


/*
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42
2012-01-11 => 1 = 7.1
Error: too large a number.
*/