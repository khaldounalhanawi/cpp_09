#include <sys/time.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include "utility.hpp"
#include "types.hpp"
#include "FordJohnsonSort.hpp"
#include <cerrno>
#include <climits>
#include <ctime>
#include <exception>

void	tester(const t_vector_ints &a, const t_vector_ints &b)
{
	if (a == b)
		std::cout << "MATCH!" << std::endl;
	else
		std::cout << "xxxx FAIL xxxx" << std::endl;
}

long	getTimePrecise()
{
	timeval	tp;

	if (gettimeofday(&tp, NULL) == -1)
		exit (3);
	long sec = tp.tv_sec;
	long usec = tp.tv_usec;

	long realReadUs = (1000000 * sec) + usec;
	return (realReadUs);
}

void	returnErrorMsg(const std::string &message, int errorNumber)
{
	std::cerr	<<	message	<< std::endl;
	std::exit (errorNumber);
}

int	safeAtol(const char *str)
{
	char	*end = NULL;
	errno = 0;

	long	val = std::strtol(str, &end, 10);

	if (*end != 0
		|| *end == *str
		|| errno == ERANGE
		|| val > INT_MAX
		|| val < INT_MIN
		|| val < 0)
		throw std::runtime_error ("ERROR");
	
	return (static_cast<int>(val));
}

t_vector_ints	parseAsVector(int argc, char **argv)
{
	t_vector_ints	values;

	for (int i = 1; i < argc; ++i)
	{
		try
		{ values.push_back (safeAtol (argv[i])); }
		catch (...)
		{ returnErrorMsg ("Error", 2);}
	}
	return (values);
}

int	main(int argc, char **argv)
{
	// checks
	if (argc < 2)
		returnErrorMsg ("You must provide atleast 1 argument to program", 1);

	// record time
	long firstRead = getTimePrecise();

	// Vector operations
	t_vector_ints input = parseAsVector (argc, argv);
	t_vector_ints ordered = FordJohnsonSort (input);

	// record time
	long secondRead = getTimePrecise();

	// calculate duration for Vector operations
	long duration = secondRead - firstRead;

	// deque thingy

	// test correctness
	t_vector_ints computerSorted (input);
	std::sort (computerSorted.begin(), computerSorted.end());
	tester (ordered, computerSorted);

	// print Before/After
	std::cout	<< "Before:";
	printVectorInts (input);
	std::cout	<< "After:";
	printVectorInts (ordered);

	// print Benchmarks
	std::cout	<< "Time to process a range of "
				<< input.size()
				<< " elements with std::vector : "
				<< duration
				<< " us\n";

	return (0);
}

// ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`
// make: warning:  Clock skew detected.  Your build may be incomplete.

/*
Before: 3 5 9 7 4
After: 3 4 5 7 9
Time to process a range of 5 elements with std::[..] : 0.00031 us
Time to process a range of 5 elements with std::[..] : 0.00014 us
*/
