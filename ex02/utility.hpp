#ifndef UTILITY_HPP
# define UTILITY_HPP

# include "types.hpp"

// print functions
void	printVectorPairs(t_vector_pairs &pairs);
void	printVectorInts(t_vector_ints &ints);

// return functions
void	returnErrorMsg(const std::string &message, int errorNumber);

// testers
void	testMatch(const t_vector_ints &a, const t_vector_ints &b);

// time functions
long	getTimePrecise();

// converter functions
int		safeAtoi(const char *str);

#endif