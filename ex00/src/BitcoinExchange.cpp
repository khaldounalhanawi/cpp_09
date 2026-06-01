#include <iostream>
#include <limits>
#include <iomanip>
#include <string>
#include "buildDataBase.hpp"
#include "types.hpp"
#include "stringManipulation.hpp"
#include "validateDate.hpp"
#include <fstream>

enum parseStatus
{
	OK,
	BAD_INPUT,
	NEGATIVE,
	TOO_LARGE
};

parseStatus	convertToDouble (const char *str, double &value);
parseStatus	createCell (const std::string &temp, const char delimiter,t_pairStr &cell);
void		reportStatus (const parseStatus status, const char *source);
void		printExchange (const t_pairStr &cell, const double value);

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
		parseStatus cellStatus = createCell (temp, delimiter, cell);
		if (cellStatus != OK)
		{
			reportStatus (cellStatus, temp.c_str ());
			continue;
		}

		// validate the date
		if (!validateDate (cell.first))
		{
			reportStatus (BAD_INPUT, cell.first.c_str());
			continue;
		}

		// convert value to double
		double valueDouble;
		parseStatus convertStatus = convertToDouble (cell.second.c_str(), valueDouble);
		if (convertStatus != OK)
		{
			reportStatus (convertStatus, cell.second.c_str());
			continue;
		}

		// get closest lower bound
		t_map::const_iterator DataIndex = data.lower_bound (cell.first);
		if (DataIndex == data.end())
		{
			std::cout << "no find." << "\n"; // look closer
			continue;
		}
		else if ((*DataIndex).first != cell.first && DataIndex != data.begin()) // checks mate
		{
			-- DataIndex;
		}

		// print out
		double rate = data.at((*DataIndex).first);
		printExchange (cell, valueDouble * rate);
	}
	return (true);
}

void	printExchange(const t_pairStr &cell, const double value)
{
	std::cout	<< cell.first
				<< " => "
				<< cell.second
				<< " = "
				<< std::setprecision(15)
				<< value
				<< "\n";
}

parseStatus	convertToDouble(const char *str, double &value)
{
	char *end = NULL;
	value = std::strtod (str, &end);

	if (end == str || *end != '\0')
		return (BAD_INPUT);
	else if (value < 0)
		return (NEGATIVE);
	else if (value > INT_MAX)
		return (TOO_LARGE);
	
	return (OK);
}

void	reportStatus(const parseStatus status, const char *source)
{
	switch (status)
	{
		case OK:
			break;
		case BAD_INPUT:
			std::cout << "bad input => " << source << "\n";
			break;
		case NEGATIVE:
			std::cout << "Error: not a positive number." << "\n";
			break;
		case TOO_LARGE:
			std::cout << "Error: too large a number." << "\n";
			break;
	}
}

parseStatus	createCell(const std::string &temp, const char delimiter,t_pairStr &cell)
{
	if (!splitStr (temp, delimiter, cell))
		return (BAD_INPUT);
	trimStr(cell.first);
	trimStr(cell.second);
	return (OK);
}

// should i do c_str()??
