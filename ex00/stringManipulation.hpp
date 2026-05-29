#ifndef STRINGMANIPULATION_HPP
# define STRINGMANIPULATION_HPP

# include <string>
# include <utility>

typedef std::pair<std::string, std::string> t_pairStr;

void	trimStr(std::string &str);
bool	splitStr(const std::string &str, char &delimiter, t_pairStr &outPair);

#endif