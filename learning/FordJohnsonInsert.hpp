#ifndef FORDJOHNSONINSERT_HPP
# define FORDJOHNSONINSERT_HPP

# include "types.hpp"

t_vector_ints::iterator	binaryFindPos(t_vector_ints::iterator start,
									t_vector_ints::iterator finish, int val);
void					mergeInsert(std::pair<int, int>	&myPair, t_vector_ints &thisVector);

#endif