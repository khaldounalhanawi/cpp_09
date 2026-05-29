#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <cstdlib>
#include "types.hpp"
#include "validateDate.hpp"
#include "stringManipulation.hpp"

typedef std::pair<std::string, std::string> t_pairStr;

static void	warning(std::string msg, std::string content, int line);

void	extractData(t_map &data, char delimiter, const char *path)
{
	// open file
	std::ifstream file(path);
	if (!file)
		throw std::runtime_error ("Failed to open Database!");

	// read lines
	int	counter = 0;
	std::string temp;
	while (std::getline (file, temp))
	{
		counter ++;

		// skip if line is empty
		if (temp.empty())
			continue;

		// split string into a pair of strings
		t_pairStr cell;
		if (!splitStr (temp, delimiter, cell))
		{
			warning("Invalid cell", temp, counter);
			continue;
		}

		// trim the strings of left and right whitespace
		trimStr(cell.first);
		trimStr(cell.second);

		// validate the date
		if (!validateDate (cell.first))
		{
			warning ("Invalid date", temp, counter);
			continue;
		}

		// convert to value to double
		char *end = nullptr;
		double valueDouble = std::strtod (cell.second.c_str(), &end);

		if (end == cell.second.c_str() || *end != '\0')
		{
			warning ("Invalid value", temp, counter);
			continue;
		}

		// insert date&value into DataBase
		std::pair<t_map::iterator, bool> inserted =
			data.insert (std::make_pair(cell.first, valueDouble));
		
		if (!inserted.second)
			warning ("Duplicate discarded", temp, counter);
	}
	return;
}

static void	warning(std::string msg, std::string content, int line)
{
	std::cout	<< "Warning: @line:" << line <<" | " + msg << " >>" + content
				<< std::endl;
}