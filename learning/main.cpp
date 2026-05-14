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

void	orderFirst(t_vector_pairs &pairs) // ⚠️ implement my own sort
{
	std::sort(pairs.begin(), pairs.end());
	return ;
}

void	mergeFirst(t_vector_pairs &pairs, t_vector_ints &thisVector)
{
	for (t_vector_pairs::iterator i = pairs.begin(); i != pairs.end(); i ++)
		thisVector.push_back ((*i).first);
	return;
}

t_vector_ints::iterator binaryFind(t_vector_ints::iterator start, t_vector_ints::iterator finish, int val)
{
	int	len = std::distance (start, finish);
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
		return (binaryFind ((start + (len / 2) + 1), finish, val));
	else
		return (binaryFind (start , (start + (len / 2)), val));
}


void	mergeInsert(std::pair<int, int>	&myPair, t_vector_ints &thisVector)
{
	t_vector_ints::iterator	matchAddress;
	t_vector_ints::iterator	pos;

	// find First address in vector
	matchAddress = std::find(thisVector.begin(), thisVector.end(), myPair.first);

	// locate proper position for Second & merge
	pos = binaryFind (thisVector.begin(), matchAddress, myPair.second);
	thisVector.insert (pos, myPair.second);

	return;
}

void	mergeSecond(t_vector_pairs &pairs, t_vector_ints &thisVector)
{
	t_vector_sizeT	jSequence;

	jSequence = generate_jSequence(pairs.size());

	// loop through jSequence & insert in reverese
	for (t_vector_sizeT::iterator itr = jSequence.begin() + 3; itr != jSequence.end(); itr ++)
	{
		size_t	lowerBound = *(itr - 1);
		size_t	upperBound = *(itr);

		while (upperBound > lowerBound)
		{
			if (upperBound > pairs.size())
				upperBound = pairs.size();
			mergeInsert (pairs.at(upperBound - 1), thisVector);
			upperBound --;
		}
	}
	return ;
}

int	main()
{
	t_vector_ints	input;
	t_vector_ints	ordered;
	t_vector_pairs	pairs;
	bool			odd;

	input.push_back (4);
	input.push_back (7);
	input.push_back (5);
	input.push_back (1);
	input.push_back (3);
	input.push_back (2);
	input.push_back (7);
	input.push_back (8);
	input.push_back (6);
	input.push_back (9);

	odd = (input.size() % 2);

	// create pairs ✅
	pairs = fillPairs (input.begin(), input.end() - odd);
	printVectorPairs (pairs);
	std::cout<< "*************************\n";

	// order high values in pairs 
	orderFirst(pairs); // implement my own sort ⚠️
	printVectorPairs (pairs);
	std::cout<< "*************************\n";

	// merge high to ordered ✅
	mergeFirst (pairs, ordered);
	printVectorInts (ordered);
	std::cout<< "\n*************************\n";

	// merge low to ordered ✅
	//   first one is a freebie
	ordered.insert (ordered.begin(), (*pairs.begin()).second);
	mergeSecond (pairs, ordered);

	// insert-merge odd item at last pos ✅
	if (odd)
	{
		int	lastItem = *(input.end () - 1);
		ordered.insert (binaryFind (ordered.begin(), ordered.end(), lastItem),
						lastItem);
	}

	printVectorInts (ordered);
	std::cout<< "\n*************************\n";

	return (0);
}