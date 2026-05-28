#include <iostream>
#include <string>

// format is	Year-Month-Day
// example		1993-01-12

static int		convertToNumber	(const std::string &date, int start, int end);
static bool		validateNumbers	(int y, int m, int d);
static bool		isLeapYear		(int y);

bool	validateDate(const std::string &date)
{
	if ( date.size () != 10
	  || date[4] != '-'
	  || date[7] != '-'
	   )
		return (false);
	
	int	y = convertToNumber (date, 0, 4);
	int	m = convertToNumber (date, 5, 7);
	int	d = convertToNumber (date, 8, 10);
	if (y < 0 || m < 0 || d < 0)
		return (false);

	return (validateNumbers(y, m, d));
}

static bool	isLeapYear(int y)
{
	return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

static bool	validateNumbers(int y, int m, int d)
{
	if (m < 1 || m > 12 || y < 0)
		return (false);

	int monthDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

	if (isLeapYear (y) && m == 2)
		return (d >= 1 && d <= 29);

	return (d >= 1 && d <= monthDays[m - 1]);
}

static int	convertToNumber(const std::string &date, int start, int end)
{
	int	value = 0;
	
	for (int i = start; i < end; ++i)
	{
		if (date[i] < '0' || date[i] > '9')
			return (-1);
		value = (value * 10) + (date[i] - '0');
	}
	return (value);
}

static int	unitTester()
{
	{
		std::cout << "\n***** test1 = 1980 *****\n";
		std::string	date = "1980";
		std::cout << convertToNumber (date, 0, 4);
	}

	{
		std::cout << "\n***** test2 = Accepted *****\n";
		std::string	status[2] = {"Denied", "Accepted"};
		std::string	date = "1980-12-09";
		std::cout << "date is "<< status[validateDate (date)];
	}

	{
		std::cout << "\n***** test3 = Denied *****\n";
		std::string	status[2] = {"Denied", "Accepted"};
		std::string	date = "1980-2-09";
		std::cout << "date is "<< status[validateDate (date)];
	}

	{
		std::cout << "\n***** test4 = Denied *****\n";
		std::string	status[2] = {"Denied", "Accepted"};
		std::string	date = "1980-12-9";
		std::cout << "date is "<< status[validateDate (date)];
	}

	{
		std::cout << "\n***** test4 = Denied *****\n";
		std::string	status[2] = {"Denied", "Accepted"};
		std::string	date = "1980-12-99";
		std::cout << "date is "<< status[validateDate (date)];
	}

	{
		std::cout << "\n***** test5 = Accepted *****\n";
		std::string	status[2] = {"Denied", "Accepted"};
		std::string	date = "0001-01-01";
		std::cout << "date is "<< status[validateDate (date)];
	}

	return (0);
}