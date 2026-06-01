#include <string>
#include <map>
#include "types_str.hpp"

void	trimStr(std::string &str)
{
	std::string whiteSpace = " \t";
	
	size_t lPos = str.find_first_not_of (whiteSpace, 0);
	if (lPos == std::string::npos)
	{
		str.clear();
		return;
	}
	size_t rPos = str.find_last_not_of(whiteSpace);
	str = str.substr(lPos, rPos - lPos + 1);
	return;
}

bool	splitStr(const std::string &str, const char &delimiter, t_pairStr &outPair)
{
	// find position of delimiter in string
	size_t delimiterPos = str.find (delimiter, 0);
	if (delimiterPos == std::string::npos
		|| delimiterPos == 0
		|| delimiterPos == str.size () - 1)
		return (false);

	// set first in outPair
	outPair.first = str.substr (0, delimiterPos);
	outPair.second = str.substr (delimiterPos + 1);

	return (true);
}
