#include <iostream>
#include <limits>
#include <iomanip>
#include <string>
#include "buildDataBase.hpp"
#include "types.hpp"
#include "stringManipulation.hpp"
#include "validateDate.hpp"

#include <fstream>

bool	BitcoinExchange(const t_map &data,const char *path, char delimiter)
{
	std::ifstream file(path);
	if (!file)
		throw std::runtime_error ("Error: could not open file.");

	// skip header
	std::string temp;
	std::getline(file, temp);

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
		t_map::const_iterator item = data.lower_bound (cell.first);
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
					<< valueDouble * data.at((*item).first)
					<< "\n";
	}
	return (true);
}
