#include <iostream>
#include <utility>
#include <vector>
#include <deque>
#include <iterator>
#include <algorithm>
#include "utility.hpp"
#include "types.hpp"
#include "jSequence.hpp"

t_vector_pairs	fillPairs(t_vector_ints::iterator first, t_vector_ints::iterator last)
{
	t_vector_pairs		pairs;
	std::pair<int, int>	temp;

	for (t_vector_ints::iterator i = first; i != last; i += 2)
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

t_vector_ints::iterator binaryFindPos(t_vector_ints::iterator start,
									t_vector_ints::iterator finish, int val)
{
	int	len = std::distance (start, finish);

	if (len == 0)
		return (start);

	if (len == 1)
	{
		if (val < *start)
			return (start);
		else
			return (finish);
	}

	if (len == 2)
	{
		if (val < *start)
			return (start);
		else if (val > *(start + 1))
			return (finish);
		else
			return (start + 1);
	}

	if (val > *(start + (len / 2)))
		return (binaryFindPos ((start + (len / 2) + 1), finish, val));
	else
		return (binaryFindPos (start , (start + (len / 2)), val));
}

void	mergeInsert(std::pair<int, int>	&myPair, t_vector_ints &thisVector)
{
	t_vector_ints::iterator	matchAddress;
	t_vector_ints::iterator	pos;

	// find First address in vector
	matchAddress = std::find(thisVector.begin(), thisVector.end(), myPair.first);

	// locate proper position for Second & merge
	pos = binaryFindPos (thisVector.begin(), matchAddress, myPair.second);
	thisVector.insert (pos, myPair.second);

	return;
}

// Jackobsthal sequence >> 0, 1, 1, 3, 5, 11, 21, 43, 85, 171, 341,…
void	mergeSeconds(t_vector_pairs &pairs, t_vector_ints &thisVector)
{
	t_vector_sizeT	jSequence;

	// first one is a freebie
	thisVector.insert (thisVector.begin(), (*pairs.begin()).second);

	if (pairs.size() <= 1)
		return ;

	jSequence = generate_jSequence(pairs.size());

	// loop through jSequence & insert in reverese
	for (t_vector_sizeT::iterator	itr = jSequence.begin() + 3;
									itr != jSequence.end(); itr ++)
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

t_vector_ints	sortTwo(t_vector_ints &input)
{
	t_vector_ints	ordered;

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

void	binaryMergeLast(t_vector_ints &intVector, t_vector_ints &input)
{
	t_vector_ints::iterator	pos;
	int						lastItem = *(input.end () - 1);

	pos = binaryFindPos (intVector.begin(), intVector.end(), lastItem);
	intVector.insert (pos, lastItem);
	return ;
}

t_vector_ints	FordJohnsonSort(t_vector_ints &input)
{
	t_vector_ints	final;
	t_vector_pairs	pairs;
	t_vector_ints	firsts;
	t_vector_ints	orderedFirsts;
	bool			odd;

	if (input.size() == 1)
		return (t_vector_ints (1, *input.begin()));

	if (input.size() == 2)
		return (sortTwo (input));

	// determind if ODD
	odd = (input.size() % 2);

	// create pairs
	pairs = fillPairs (input.begin(), input.end() - odd);

	// create firsts vector
	for (t_vector_pairs::iterator i = pairs.begin(); i != pairs.end(); i ++)
		firsts.push_back ((*i).first);

	// order firsts recursively
	orderedFirsts = FordJohnsonSort (firsts);

	// push orderedFirsts to final
	for (size_t i = 0 ; i < orderedFirsts.size(); i ++)
		final.push_back (orderedFirsts[i]);

	// remap pairs basing on orderedFirsts
	pairs = mapPairs (pairs, orderedFirsts);

	// merge Seconds to final ordered:
	mergeSeconds (pairs, final);

	// binary merge odd item at last pos
	if (odd)
		binaryMergeLast (final, input);

	return (final);
}
