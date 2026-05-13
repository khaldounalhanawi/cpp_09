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

void	orderFirst(vector__pairs &pairs)
{
	std::sort(pairs.begin(), pairs.end());
	return ;
}

vector__ints	pMerge(vector__pairs &pairs)
{
	vector__ints	myVector;
	int				e = (*(pairs.end() - 1)).second;
	int				a1 = (*pairs.begin()).first;
	int				b1 = (*pairs.begin()).second;
	int				a2 = (*(pairs.begin() + 1)).first;
	// int				b2 = (*(pairs.begin() + 1)).second;

	myVector.push_back (b1);
	myVector.push_back (a1);
	myVector.push_back (a2);

	if (e < b1)
		myVector.insert(myVector.begin(), e);
	else if (e < a1)
		myVector.insert(myVector.begin() + 1, e);
	else if (e < a2)
		myVector.insert(myVector.begin() + 2, e);

	return (myVector);
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

//Jn​=Jn−1​+2Jn−2​

int	main()
{
	vector__ints	input;
	vector__ints	jSequence;
	vector__ints	final;
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
	// input.push_back (9); // handle odd later

	// generate jSequence
	jSequence = generate_jSequence(input.size() / 2);
	printVectorInts (jSequence); // tester
	std::cout<< "\n*************************\n";

	// create pairs
	odd = (input.size() % 2);
	pairs = fillPairs (input.begin(), input.end() - odd);
	printVectorPairs (pairs);
	std::cout<< "*************************\n";

	// order high values in pairs
	orderFirst(pairs); // implement my own sort
	printVectorPairs (pairs);
	std::cout<< "*************************\n";

	// merge to final
	final = (pMerge(pairs));
	printVectorInts (final);
	std::cout<< "\n*************************\n";

	return (0);
}