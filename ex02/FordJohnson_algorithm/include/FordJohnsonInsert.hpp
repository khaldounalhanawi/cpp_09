#ifndef FORDJOHNSONINSERT_HPP
# define FORDJOHNSONINSERT_HPP

# include "types.hpp"

// vector version
t_vector_ints::iterator	binaryFindPos(t_vector_ints::iterator start,
									t_vector_ints::iterator finish, int val);
void					mergeInsert(std::pair<int, int>	&myPair, t_vector_ints &thisVector);

// deque version
t_deque_ints::iterator	binaryFindPos(t_deque_ints::iterator start,
									t_deque_ints::iterator finish, int val);
void					mergeInsert(std::pair<int, int>	&myPair, t_deque_ints &thisVector);

#endif