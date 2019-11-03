#include "Parser.h"

void parse_file(std::string file_name) {
	std::string line;
	std::ifstream myfile(file_name+".txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			
		}
		myfile.close();
	}
}