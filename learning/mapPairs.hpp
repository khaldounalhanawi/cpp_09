#ifndef MAPPAIRS_HPP
# define MAPPAIRS_HPP

# include "types.hpp"

t_vector_pairs	mapPairs(t_vector_pairs &pairs, t_vector_ints &orderedFirsts);

// deque version
t_deque_pairs	mapPairs_deque(t_deque_pairs &pairs, t_deque_ints &orderedFirsts);

#endif