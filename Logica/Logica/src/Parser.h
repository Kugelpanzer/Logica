#include<string>
#include<fstream>
#include"Gate.h"
#include<vector>
#include<iostream>
#pragma once

void parse_file(std::string file_name,std::vector<Gate> &stateMachine, std::vector<std::string>&inputList, std::vector<std::string>&outputList,std::vector<int> &weightList);

void reverse_parse_file(std::string file_name);


/*
weight has same address as outValue ,
outPoint, inPoint is showing to which list is adrress pointing(outputList or inputList)
*/
struct textGate {
	bool notInvert=true;

	int weight = 0;
	int outAddress = 0, inAddress = 0;
	std::string outValue="", inValue="";
	char outPoint='o', inPoint='i';

	std::vector<int> gateAddress;
	std::vector<bool> notInverted;
};

void WriteTextGate(textGate);