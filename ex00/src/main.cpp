#include <iostream>
#include <iomanip>
#include <string>
#include "buildDataBase.hpp"
#include "types.hpp"

int	main()
{
	t_map	data;

	try { buildDataBase (data, ',', "assets/data.csv", true); }
	catch (const std::runtime_error &e) { std::cerr << e.what(); return (1); }

	for (t_map::iterator i  = data.begin(); i != data.end(); ++i)
		std::cout << i->first << "   ===   " << std::setprecision(15) << i->second << "\n";

	return (0);
}