#ifndef STRINGMANIPULATION_HPP
# define STRINGMANIPULATION_HPP

# include <string>
# include <utility>
# include "types_str.hpp"

void	trimStr (std::string &str);
bool	splitStr (const std::string &str, const char &delimiter, t_pairStr &outPair);

#endif