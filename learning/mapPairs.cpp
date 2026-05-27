#include <vector>
#include "types.hpp"

t_deque_pairs	mapPairs_deque(t_deque_pairs &pairs, t_deque_ints &orderedFirsts)
{
	t_deque_pairs		orderedPairs;
	std::deque<bool>	used(pairs.size(), false);

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
