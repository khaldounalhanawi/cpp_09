#include <iostream>
#include <utility>
#include <vector>
#include <deque>
#include <iterator>
#include <algorithm>

typedef std::vector< int >					t_vector_ints;
typedef std::vector< std::pair<int, int> >	t_vector_pairs;

void	printVectorPairs(t_vector_pairs &pairs)
{
	for(t_vector_pairs::iterator i = pairs.begin(); i != pairs.end(); i++)
		std::cout <<"(" << (*i).first << ", " << (*i).second << ")" << "\n";
}

void	printVectorInts(t_vector_ints &ints)
{
	for(t_vector_ints::iterator i = ints.begin(); i != ints.end(); i++)
		std::cout << *i << ", ";
}

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

t_vector_ints	generate_jSequence(int len)
{
	t_vector_ints	sequence;
	int				i;
	int				val;
	
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


void	myMerge(std::pair<int, int>	&myPair, t_vector_ints &thisVector)
{
	t_vector_ints::iterator	matchAddress;
	t_vector_ints::iterator	pos;

	// find upper First position
	matchAddress = std::find(thisVector.begin(), thisVector.end(), myPair.first);

	// find proper position & merge
	pos = binaryFind (thisVector.begin(), matchAddress, myPair.second);
	thisVector.insert (pos, myPair.second);

	return;
}

void	mergeSecond(t_vector_pairs &pairs, t_vector_ints &thisVector) // 🚧
{
	t_vector_ints	jSequence;

	jSequence = generate_jSequence(pairs.size());
	printVectorInts (jSequence); // tester
	std::cout<< "\n***********was sequence**************\n";

	// for each pair
	// loop through jsequence
	for (t_vector_ints::iterator i = jSequence.begin() + 3; i != jSequence.end(); i ++) // 🚧
	{
		int	min = *(i - 1);
		int	max = *(i);

		while (max > min)
		{
			try { myMerge (pairs.at(max - 1), thisVector); } // ⚠️ also better control against size!!!
			catch (...){};
			max --;
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
	input.push_back (5);
	input.push_back (1);
	input.push_back (3);
	input.push_back (2);
	input.push_back (7);
	input.push_back (8);
	input.push_back (-1);
	// input.push_back (9); // handle odd later ⚠️

	// create pairs ✅
	odd = (input.size() % 2);
	pairs = fillPairs (input.begin(), input.end() - odd);
	printVectorPairs (pairs);
	std::cout<< "*************************\n";

	// order high values in pairs ⚠️
	orderFirst(pairs); // implement my own sort ⚠️
	printVectorPairs (pairs);
	std::cout<< "*************************\n";

	// merge high to ordered ✅
	mergeFirst (pairs, ordered);
	printVectorInts (ordered);
	std::cout<< "\n*************************\n";

	// merge low to ordered 🚧
	//   first one is a freebie
	ordered.insert (ordered.begin(), (*pairs.begin()).second);
	mergeSecond (pairs, ordered); // 🚧
	printVectorInts (ordered);
	std::cout<< "\n*************************\n";

	return (0);
}