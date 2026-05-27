# include <iostream>
# include "types.hpp"

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
