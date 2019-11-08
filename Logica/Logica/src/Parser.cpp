#include "Parser.h"
#include <stdarg.h>
#include<fstream>
#include<string>
#include <algorithm>



void parse_file(std::string file_name,std::vector<Gate> &stateMachine,std::vector<std::string> &inputList,std::vector<std::string> &outputList) {
	std::string line;
	std::ifstream myfile(file_name+".txt");
	if (myfile.is_open())
	{
		/*
		
		*/
		while (getline(myfile, line))
		{
			line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
			std::vector<std::string> section = str_split(line, ":");
			if (section.size == 2) {
				if (section[1].front == '(' && section[1].back==')') {
					section[1].erase(section[1].length - 1);
					section[1].erase(0);

				}
				else {

				}
			}
			else if (section.size == 3) {

			}
		}
		myfile.close();
	}
}



std::vector<std::string> str_split(std::string str, std::string delimiter) {

	int pos = 0;
	std::string token;
	std::vector<std::string> ret;
	while ((pos = str.find(delimiter)) != std::string::npos) {
		token = str.substr(0, pos);
		ret.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	ret.push_back(str);

	return ret;
}