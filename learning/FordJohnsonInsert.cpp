#include "types.hpp"

t_vector_ints::iterator	binaryFindPos(t_vector_ints::iterator start,
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
