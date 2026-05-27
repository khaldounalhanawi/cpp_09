#include <iostream>
#include <algorithm>
#include "utility.hpp"
#include "types.hpp"
#include "FordJohnsonSort.hpp"

static t_vector_ints	parseAsVector(int argc, char **argv);
static t_deque_ints		parseAsDeque(int argc, char **argv);
static void				printTiming(const std::string &container, int size, long duration);

int	main(int argc, char **argv)
{
	// checks
	if (argc < 2)
		returnErrorMsg ("Program needs a minimum of 1 argument", 1);

	// record time
	long firstRead = getTimePrecise();

	// Vector operations
	t_vector_ints input =	parseAsVector (argc, argv);
	t_vector_ints ordered =	FordJohnsonSort (input);

	// record time
	long secondRead = getTimePrecise();

	// calculate duration for Vector operations
	long duration = secondRead - firstRead;

	// deque Version
	long			firstRead_Deque =	getTimePrecise();
	t_deque_ints	input_Deque =		parseAsDeque (argc, argv);
	t_deque_ints	ordered_Deque =		FordJohnsonSort (input_Deque);
	long			secondRead_Deque =	getTimePrecise();
	long			duration_Deque =	secondRead_Deque - firstRead_Deque;
	
	// test order correctness
	t_vector_ints computerSorted (input);
	std::sort (computerSorted.begin(), computerSorted.end());
	testMatch (ordered, computerSorted);

	// print Before/After
	std::cout	<< "Before:";
	printVectorInts (input);
	std::cout	<< "After:";
	printVectorInts (ordered);

	// print Benchmarks
	printTiming ("std::vector", input.size(), duration);
	printTiming ("std::deque", input.size(), duration_Deque);

	return (0);
}

static t_vector_ints	parseAsVector(int argc, char **argv)
{
	t_vector_ints	values;

	for (int i = 1; i < argc; ++i)
	{
		try
		{ values.push_back (safeAtoi (argv[i])); }
		catch (const std::exception &e)
		{ returnErrorMsg ("Error", 2);}
	}
	return (values);
}

static t_deque_ints	parseAsDeque(int argc, char **argv)
{
	t_deque_ints	values;

	for (int i = 1; i < argc; ++i)
	{
		try
		{ values.push_back (safeAtoi (argv[i])); }
		catch (const std::exception &e)
		{ returnErrorMsg ("Error", 2);}
	}
	return (values);
}

static void	printTiming(const std::string &container, int size, long duration)
{
	std::cout	<< "Time to process a range of "
				<< size
				<< " elements with "
				<< container
				<< " : "
				<< duration
				<< " us\n";
	return;
}

// ./PmergeMe `shuf -i 1-100000 -n 3000 | tr "\n" " "`