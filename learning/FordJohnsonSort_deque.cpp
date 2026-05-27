#include "types.hpp"
#include "mapPairs.hpp"
#include "FordJohnsonInsert.hpp"
#include "jSequence.hpp"

static t_deque_ints		sortTwo (t_deque_ints &input);
static t_deque_pairs	fillPairs (t_deque_ints::iterator first, t_deque_ints::iterator last);
static void				mergeSeconds (t_deque_pairs &pairs, t_deque_ints &thisVector);
static void				binaryMergeLast (t_deque_ints &intVector, t_deque_ints &input);

t_deque_ints	FordJohnsonSort(t_deque_ints &input)
{
	t_deque_pairs	pairs;
	t_deque_ints	firsts;
	t_deque_ints	orderedFirsts;
	bool			odd;

	if (input.size() == 1)
		return (t_deque_ints (1, *input.begin()));

	if (input.size() == 2)
		return (sortTwo (input));

	// determind if ODD
	odd = (input.size() % 2);

	// create pairs
	pairs = fillPairs (input.begin(), input.end() - odd);

	// create firsts vector
	for (t_deque_pairs::iterator i = pairs.begin(); i != pairs.end(); ++i)
		firsts.push_back ((*i).first);

	// order firsts recursively
	orderedFirsts = FordJohnsonSort (firsts);

	// push orderedFirsts to final
	t_deque_ints	final(orderedFirsts);

	// remap pairs basing on orderedFirsts
	pairs = mapPairs_deque (pairs, orderedFirsts);

	// merge Seconds to final ordered:
	mergeSeconds (pairs, final);

	// binary merge odd item at last pos
	if (odd)
		binaryMergeLast (final, input);

	return (final);
}

static t_deque_pairs	fillPairs(t_deque_ints::iterator first, t_deque_ints::iterator last)
{
	t_deque_pairs		pairs;
	std::pair<int, int>	temp;

	for (t_deque_ints::iterator i = first; i != last; i += 2)
	{
		if (*i > *(i + 1))
		{
			temp.first = *i;
			temp.second = *(i + 1);
		}
		else
		{
			temp.first = *(i + 1);
			temp.second = *i;
		}
		pairs.push_back (temp);
	}
	return (pairs);
}

static void	mergeSeconds(t_deque_pairs &pairs, t_deque_ints &thisVector)
{
	t_deque_sizeT	jSequence;

	// first one is a freebie
	thisVector.insert (thisVector.begin(), (*pairs.begin()).second);

	if (pairs.size() <= 1)
		return ;

	// Jackobsthal sequence >> 0, 1, 1, 3, 5, 11, 21, 43, 85, 171, 341,…
	jSequence = generate_jSequence_deque(pairs.size());

	// loop through jSequence & insert in reverese
	for (t_deque_sizeT::iterator	itr = jSequence.begin() + 3;
									itr != jSequence.end(); ++itr)
	{
		size_t	lowerBound = *(itr - 1);
		size_t	upperBound = *(itr);

		while (upperBound > lowerBound)
		{
			if (upperBound > pairs.size())
				upperBound = pairs.size();
			if (upperBound <= lowerBound)
				break;
			mergeInsert (pairs.at (upperBound - 1), thisVector);
			upperBound --;
		}
	}
	return ;
}

static t_deque_ints	sortTwo(t_deque_ints &input)
{
	t_deque_ints	ordered;

	if (*input.begin() > *(input.end() - 1))
	{
		ordered.push_back (*(input.end() - 1));
		ordered.push_back (*input.begin());
	}
	else
	{
		ordered.push_back (*input.begin());
		ordered.push_back (*(input.end() - 1));
	}
	return (ordered);
}

static void	binaryMergeLast(t_deque_ints &intVector, t_deque_ints &input)
{
	t_deque_ints::iterator	pos;
	int						lastItem = *(input.end () - 1);

	pos = binaryFindPos (intVector.begin(), intVector.end(), lastItem);
	intVector.insert (pos, lastItem);
	return ;
}
