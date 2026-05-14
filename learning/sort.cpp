#include <iostream>
#include <vector>

std::vector<int>::iterator mySort(std::vector<int>::iterator start, std::vector<int>::iterator finish, int val)
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
		return (mySort ((start + (len / 2) + 1), finish, val));
	else
		return (mySort (start , (start + (len / 2)), val));
}

int	main()
{
	std::vector<int>	original;

	original.push_back (0);
	original.push_back (3);
	original.push_back (5);
	original.push_back (9);
	original.push_back (12);
	original.push_back (13);

	int	test_val = 22;

	std::vector<int>::iterator pos = mySort (original.begin(), original.end(), test_val);

	// std::cout<< "***\n";
	// std::cout<< *pos << "\n";
	// std::cout<< "***\n";
	// return 0;

	original.insert (pos, test_val);

	for (int i = 0; i < 7; i++)
		std::cout<< original[i] << "\n";

		return (0);
}