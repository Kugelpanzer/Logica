#include<string>
#include<fstream>
#include"Gate.h"
#include<vector>
#include<iostream>
#pragma once

void parse_file(std::string file_name,std::vector<Gate> &stateMachine, std::vector<std::string>&inputList, std::vector<std::string>&outputList, std::vector<int> &inputWeightList, std::vector<int> &outputWeightList);

void reverse_parse_file(std::string file_name, std::vector<Gate> &stateMachine);


/*
weight has same address as outValue ,
outPoint, inPoint is showing to which list is adrress pointing(outputList or inputList)
*/
struct TextGate {
	int id;
	bool notInvert=true;

	int weight = 0;
	int outAddress = -1, inAddress = -1;
	std::string outValue="", inValue="";
	char outPoint='o', inPoint='i';

	std::vector<int> gateAddress;
	std::vector<bool> notInverted;
};

void WriteTextGate(TextGate gate);