#include <iostream>
#include <climits>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <fstream>
#include "types.hpp"
#include "stringManipulation.hpp"
#include "validateDate.hpp"

enum parseStatus
{
	OK,
	BAD_INPUT,
	NEGATIVE,
	TOO_LARGE
};

parseStatus	convertToDouble (const std::string &inputString, double &value);
parseStatus	createCell (const std::string &temp, const char delimiter,t_pairStr &cell);
parseStatus	browseRate(const t_map &data, const std::string &input, double &value);
void		reportStatus (const parseStatus status, const std::string &source);
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
			reportStatus (cellStatus, temp);
			continue;
		}

		// validate the date
		if (!validateDate (cell.first))
		{
			reportStatus (BAD_INPUT, cell.first);
			continue;
		}

		// convert value to double
		double valueDouble;
		parseStatus convertStatus = convertToDouble (cell.second, valueDouble);
		if (convertStatus != OK)
		{
			reportStatus (convertStatus, cell.second);
			continue;
		}

		// get closest lower bound
		double rate;
		parseStatus browseStatus = browseRate (data, cell.first, rate);
		if (browseStatus != OK)
		{
			reportStatus (browseStatus, cell.first);
			continue;
		}

		// print out
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

parseStatus	convertToDouble(const std::string &inputString, double &value)
{
	const char *str = inputString.c_str ();
	char *end = NULL;
	value = std::strtod (str, &end);

	if (end == str || *end != '\0')
		return (BAD_INPUT);
	else if (value < 0)
		return (NEGATIVE);
	else if (value > 1000)
		return (TOO_LARGE);
	
	return (OK);
}

void	reportStatus(const parseStatus status, const std::string &source)
{
	switch (status)
	{
		case OK:
			break;
		case BAD_INPUT:
			std::cout << "Error: bad input => " << source << "\n";
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

parseStatus	browseRate(const t_map &data, const std::string &input, double &value)
{
	if (data.empty ())
		throw std::runtime_error ("empty data base");

	if (input < data.begin ()->first)
		return (BAD_INPUT);

	t_map::const_iterator DataIndex = data.lower_bound (input);

	if (DataIndex == data.end())
		-- DataIndex;

	else if ((*DataIndex).first != input && DataIndex != data.begin())
	{
		-- DataIndex;
	}
	value = DataIndex->second;
	return (OK);
}
