#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>

typedef std::map<std::string, double> t_map;

#include <cstdlib>
void	dataExtractor(t_map &data, char delimiter, const char *path)
{
	std::fstream	file;
	std::string		temp;

	file.open(path, std::fstream::in);
	if (!file)
		throw std::runtime_error ("Failed to open Database! \n");

	while (std::getline (file, temp))
	{
		if (temp.size () == 0)
			continue;
		size_t commaAt = temp.find (delimiter, 0);
		if (commaAt == std::string::npos || commaAt == 0 || commaAt == temp.size () - 1)
		{
			std::cout	<< "Invalid data base cell @" 
						<< temp
						<< std::endl;
			continue;
		}
		std::string date = temp.substr (0, commaAt);
		std::string value = temp.substr (commaAt + 1, temp.size ());

		char *end = nullptr;
		double valueDouble = std::strtod (value.c_str(), &end);
		if (*end == *value.begin() || *end != 0)
		{
			std::cout	<< "Invalid data base value @" 
						<< date
						<< " "
						<< value
						<< std::endl;
			continue;
		}
		data[date] = valueDouble;
	}
	file.close(); // error check?
	return ;
}


int	main()
{
	t_map	data;

	try { dataExtractor (data, ',', "assets/data.csv"); }
	catch (std::runtime_error) { return (1); }

	for (t_map::iterator i  = data.begin(); i != data.end(); ++i)
		std::cout << i->first << "   ===   " << std::setprecision(15) << i->second << "\n";

	return (0);
}