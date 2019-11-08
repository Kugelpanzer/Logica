#include<string>
#include<fstream>
#include"Gate.h"
#include<vector>
#pragma once

void parse_file(std::string file_name,std::vector<Gate> &stateMachine, std::vector<std::string>&inputList, std::vector<std::string>&outputList);

void reverse_parse_file(std::string file_name);