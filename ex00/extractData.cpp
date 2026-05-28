#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>
#include "types.hpp"
#include "validateDate.hpp"

void	extractData(t_map &data, char delimiter, const char *path)
{
	std::fstream	file;
	std::string		temp;

	file.open(path, std::fstream::in);
	if (!file)
		throw std::runtime_error ("Failed to open Database!");

	while (std::getline (file, temp))
	{
		// skip epmty lines
		if (temp.empty())
			continue;

		// find position of delimiter in string
		size_t delimiterPos = temp.find (delimiter, 0);
		if (delimiterPos == std::string::npos
			|| delimiterPos == 0
			|| delimiterPos == temp.size () - 1)
		{
			std::cout	<< "Warning: Invalid data base cell @" << temp
						<< std::endl;
			continue;
		}

		// get data & validate it
		std::string date = temp.substr (0, delimiterPos);
		if (!validateDate (date))
		{
			std::cout	<< "Warning: Invalid date @" << temp
						<< std::endl;
			continue;
		}

		// get value & validate it
		std::string value = temp.substr (delimiterPos + 1, temp.size ());
		char *end = nullptr;
		double valueDouble = std::strtod (value.c_str(), &end);
		if (*end == *value.begin() || *end != 0)
		{
			std::cout	<< "Warning: Invalid value @" << temp
						<< std::endl;
			continue;
		}

		// add to DATA
		data[date] = valueDouble;
	}

	file.close();
	return;
}
