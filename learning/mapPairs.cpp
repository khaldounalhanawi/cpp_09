#include <vector>
#include "types.hpp"

t_vector_pairs	mapPairs(t_vector_pairs &pairs, t_vector_ints &orderedFirsts)
{
	t_vector_pairs		orderedPairs;
	std::vector<bool>	used(pairs.size(), false);

	for (size_t i = 0; i < orderedFirsts.size(); i++)
	{
		// Find the first UNUSED pair with this first value
		for (size_t j = 0; j < pairs.size(); j++)
		{
			if (!used[j] && pairs[j].first == orderedFirsts[i])
			{
				orderedPairs.push_back(pairs[j]);
				used[j] = true;
				break;
			}
		}
	}
	return (orderedPairs);
}
