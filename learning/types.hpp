#ifndef TYPES_HPP
# define TYPES_HPP

# include <vector>
# include <deque>
# include <utility>
# include <cstddef>

// Vector version
typedef std::vector< int >					t_vector_ints;
typedef std::vector< size_t	>				t_vector_sizeT;
typedef std::vector< std::pair<int, int> >	t_vector_pairs;

// Deque version
typedef std::deque< int >					t_deque_ints;
typedef std::deque< size_t	>				t_deque_sizeT;
typedef std::deque< std::pair<int, int> >	t_deque_pairs;

#endif