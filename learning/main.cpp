#include <iostream>
#include <vector>
#include <algorithm>
#include "utility.hpp"
#include "types.hpp"
#include "FordJohnsonSort.hpp"

void	tester(t_vector_ints a, t_vector_ints b)
{
	if (a == b)
		std::cout << "MATCH!" << std::endl;
	else
		std::cout << "xxxx FAIL xxxx" << std::endl;
}

int	main()
{
	t_vector_ints	input;
	t_vector_ints	ordered;

	input.push_back (4);
	input.push_back (1);
	input.push_back (4);
	input.push_back (1);
	input.push_back (7);
	input.push_back (5);
	input.push_back (1);
	input.push_back (3);
	input.push_back (2);
	input.push_back (0);
	input.push_back (8);
	input.push_back (6);
	input.push_back (9);
	input.push_back (0);
	input.push_back (22);
	input.push_back (-45);

	t_vector_ints	comparasion(input);
	std::sort (comparasion.begin(), comparasion.end());

	ordered = FordJohnsonSort (input);

	tester (ordered, comparasion);
	printVectorInts (ordered);
	printVectorInts (comparasion);

	return (0);
}
