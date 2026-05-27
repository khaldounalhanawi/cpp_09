#include <iostream>
#include <sys/time.h>
#include <climits>
#include <cerrno>
#include <cstdlib>
#include "types.hpp"

void	printVectorPairs(t_vector_pairs &pairs)
{
	for(t_vector_pairs::iterator i = pairs.begin(); i != pairs.end(); i++)
		std::cout <<"(" << (*i).first << ", " << (*i).second << ")" << "\n";
}

void	printVectorInts(t_vector_ints &ints)
{
	for(t_vector_ints::iterator i = ints.begin(); i != ints.end(); i++)
		std::cout << " "<< *i;
	std::cout << std::endl;
}

void	testMatch(const t_vector_ints &a, const t_vector_ints &b)
{
	if (a == b)
		std::cout << "MATCH!" << std::endl;
	else
		std::cout << "xxxx FAIL xxxx" << std::endl;
}

void	returnErrorMsg(const std::string &message, int errorNumber)
{
	std::cerr	<<	message	<< std::endl;
	std::exit (errorNumber);
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

int	safeAtoi(const char *str)
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