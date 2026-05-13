#include <iostream>
#include <utility>
#include <vector>
#include <iterator>
#include <algorithm>

typedef std::vector< int >					vector__ints;
typedef std::vector< std::pair<int, int> >	vector__pairs;

void	printVectorPairs(vector__pairs &pairs)
{
	for(vector__pairs::iterator i = pairs.begin(); i != pairs.end(); i++)
		std::cout <<"(" << (*i).first << ", " << (*i).second << ")" << "\n";
}

void	printVectorInts(vector__ints &ints)
{
	for(vector__ints::iterator i = ints.begin(); i != ints.end(); i++)
		std::cout << *i << ", ";
}

vector__pairs	fillPairs(vector__ints::iterator first, vector__ints::iterator last)
{
	vector__pairs		pairs;
	std::pair<int, int>	temp;

	for (vector__ints::iterator i = first; i != last; i += 2)
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

void	orderFirst(vector__pairs &pairs) // ⚠️
{
	std::sort(pairs.begin(), pairs.end());
	return ;
}

vector__ints	generate_jSequence(int len)
{
	vector__ints	sequence;
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

void	mergeFirst(vector__pairs &pairs, vector__ints &thisVector)
{
	for (vector__pairs::iterator i = pairs.begin(); i != pairs.end(); i ++)
		thisVector.push_back ((*i).first);
	return;
}

void	myMerge(std::pair<int, int>	&myPair, vector__ints &thisVector) // ⚠️ NEEDS a PROPER insert
{

	std::cout << "i insert " << myPair.second << std::endl;

	// find upper First position

	// merge-insert within Range
	// mergeInsert(begin, thisVector.find(myPain.first), thisVector, value);
}

void	mergeSecond(vector__pairs &pairs, vector__ints &thisVector) // 🚧
{
	vector__ints	jSequence;

	jSequence = generate_jSequence(pairs.size());
	printVectorInts (jSequence); // tester
	std::cout<< "\n***********was sequence**************\n";

	// for each pair
	// loop through jsequence
	for (vector__ints::iterator i = jSequence.begin() + 3; i != jSequence.end(); i ++) // 🚧
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
	vector__ints	input;
	vector__ints	ordered;
	vector__pairs	pairs;
	bool			odd;

	input.push_back (4);
	input.push_back (5);
	input.push_back (1);
	input.push_back (3);
	input.push_back (2);
	input.push_back (7);
	input.push_back (8);
	input.push_back (6);
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