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

int	main()
{
	vector__ints	input;
	vector__ints	final;
	vector__pairs	pairs;
	bool			odd;

	input.push_back (4);
	input.push_back (5);
	input.push_back (1);
	input.push_back (3);
	input.push_back (2);
	input.push_back (6);     // only for odd implementation

	odd = (input.size() % 2);
	pairs = fillPairs (input.begin(), input.end() - odd);
	printVectorPairs (pairs);
	std::cout<< "*************************\n";
	orderFirst(pairs); // implement my own sort
	printVectorPairs (pairs);
	std::cout<< "*************************\n";
	final = (pMerge(pairs));
	printVectorInts (final);

	return (0);
}