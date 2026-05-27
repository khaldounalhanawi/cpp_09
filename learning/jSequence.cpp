#include "types.hpp"
#include <stdexcept>

t_vector_sizeT	generate_jSequence(const size_t &len)
{
	t_vector_sizeT	sequence;
	size_t			i;
	size_t			val;
	
	if (!len)
		throw std::runtime_error ("len is too short for jSequence");

	sequence.push_back (0);
	sequence.push_back (1);
	i = 2;
	while (sequence.at(i - 1) < len)
	{
		val = sequence.at(i - 1) + 2 * (sequence.at(i - 2));
		sequence.push_back (val);
		i ++;
	}

	return (sequence);
}