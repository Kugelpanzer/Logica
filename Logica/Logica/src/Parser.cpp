#include "Parser.h"
#include <stdarg.h>
#include<fstream>
#include<string>
#include <algorithm>

std::vector<std::string> str_split(std::string str, std::string delimiter);
void WriteTextGate(TextGate gate);
Gate FromTextGateToGate(TextGate tGate, std::vector<Gate> &stateMachine, std::vector<std::string> &inputList, std::vector<std::string> &outputList, std::vector<int> &inputWeightList, std::vector<int> &outputWeightList);
std::vector<bool*> SetConnection(TextGate tGate, std::vector<Gate>&stateMachine);


void parse_file(std::string file_name,std::vector<Gate> &stateMachine,std::vector<std::string> &inputList,std::vector<std::string> &outputList, std::vector<int> &inputWeightList, std::vector<int> &outputWeightList) {
	std::string line;

	std::ifstream myfile("programs/"+file_name+".txt");
	//std::ifstream myfile(file_name + ".txt");

	std::vector<TextGate> textGateList;

	if (myfile.is_open())
	{

		/*
		if there is exclamation mark before number of gate that gate is reversed ( not gate) 
		!1:5,2,3,4
		in and out-> are used to set input and output of the list
		2:(in(5,nesto1,o),out(3,nesto,i),w(3)):[1;3;+1;!],5
		*/
		while (getline(myfile, line))
		{
			TextGate currGate;

			line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
			std::vector<std::string> section = str_split(line, ":");
			//SECTION[0] ID
			if (section[0].front() == '!') {
				currGate.notInvert = false;
				section[0].erase(0,1);
			}
			currGate.id = std::stoi(section[0]);


			//
			if (section.size() == 2) {

				if (section[1].front() == '(' && section[1].back()==')') {
					
					section[1].pop_back();
					section[1].erase(0,1);
					std::vector<std::string> arguments;

					 if(section[1].find("),") != std::string::npos)
					{
						 arguments = str_split(section[1], "),");
						 arguments.back().pop_back();
					}
					else {
						arguments.push_back(section[1]);
					}
					

					for (int i = 0; i < arguments.size(); i++) {

						std::string func = str_split(arguments[i], "(")[0];
						std::string value_string= str_split(arguments[i], "(")[1];
						

						if (func == "in") {
							std::vector<std::string> values = str_split(value_string, ",");
							currGate.inAddress = std::stoi(values[0]);
							currGate.inValue = values[1];
							currGate.inPoint = values[2].front();
						}
						else if (func == "out") {
							std::vector<std::string> values = str_split(value_string, ",");
							currGate.outAddress = std::stoi(values[0]);
							currGate.outValue = values[1];
							currGate.outPoint = values[2].front();
						}
						else if (func == "w") {
							currGate.weight = std::stoi(value_string);
						}
						else {
							std::cout << "wrong arguments for input/output: " + func;
						}

					}
				}
				else{

					std::vector<std::string> addressList = str_split(section[1], ",");

					for (int i = 0; i <addressList.size(); i++) {
						if (addressList[i].front() == '[' && addressList[i].back() == ']') {

							addressList[i].erase(0,1);
							addressList[i].pop_back();

							std::vector<std::string> for_args = str_split(addressList[i], ";");
							int from = std::stoi(for_args[0]);
							int to = std::stoi(for_args[1]);

							char oper = for_args[2].front();
							for_args[2].erase(0,1);
							int step= std::stoi(for_args[2]);
							bool notInvert = true;
							if (for_args.size() == 4) {
								notInvert = false;
							}

							switch (oper)
							{
							case '+':
								for (int i = from; i < to; i += step) {
									if (notInvert) {
										currGate.gateAddress.push_back(i);
										currGate.notInverted.push_back(true);
									}
									else {
										currGate.gateAddress.push_back(i);
										currGate.notInverted.push_back(false);
									}
								}
								break;
							case '-':
								for (int i = from; i > to; i -= step) {
									if (notInvert) {
										currGate.gateAddress.push_back(i);
										currGate.notInverted.push_back(true);
									}
									else {
										currGate.gateAddress.push_back(i);
										currGate.notInverted.push_back(false);
									}
								}
								break;
							case '*':
								for (int i = from; i < to; i *= step) {
									if (notInvert) {
										currGate.gateAddress.push_back(i);
										currGate.notInverted.push_back(true);
									}
									else {
										currGate.gateAddress.push_back(i);
										currGate.notInverted.push_back(false);
									}
								}
								break;
							case '/':
								for (int i = from; i > to; i /= step) {
									if (notInvert) {
										currGate.gateAddress.push_back(i);
										currGate.notInverted.push_back(true);
									}
									else {
										currGate.gateAddress.push_back(i);
										currGate.notInverted.push_back(false);
									}
								}
								break;
							default:
								std::cout << "wrong operator";
								break;
							}


						}
						else if (addressList[i].front() == '!') {
							addressList[i].erase(0,1);
							currGate.gateAddress.push_back(std::stoi(addressList[i]));
							currGate.notInverted.push_back(false);
						}
						else {
							currGate.gateAddress.push_back(std::stoi(addressList[i]));
							currGate.notInverted.push_back(true);
						}
					}
				}
			}
			else if (section.size() == 3) {

				//SECTION 1
				section[1].pop_back();
				section[1].erase(0,1);
				std::vector<std::string> arguments = str_split(section[1], "),");
				arguments.back().pop_back();

				for (int i = 0; i < arguments.size(); i++) {

					std::string func = str_split(arguments[i], "(")[0];
					std::string value_string = str_split(arguments[i], "(")[1];


					if (func == "in") {
						std::vector<std::string> values = str_split(value_string, ",");
						currGate.inAddress = std::stoi(values[0]);
						currGate.inValue = values[1];
						currGate.inPoint = values[2].front();
					}
					else if (func == "out") {
						std::vector<std::string> values = str_split(value_string, ",");
						currGate.outAddress = std::stoi(values[0]);
						currGate.outValue = values[1];
						currGate.outPoint = values[2].front();
					}
					else if (func == "w") {
						currGate.weight = std::stoi(value_string);
					}
					else {
						std::cout << "wrong arguments for input/output: " + func;
					}


					//SECTION 2
					std::vector<std::string> addressList = str_split(section[2], ",");

					for (int i = 0; i <addressList.size(); i++) {
						if (addressList[i].front() == '[' && addressList[i].back() == ']') {

							addressList[i].erase(0,1);
							addressList[i].pop_back();

							std::vector<std::string> for_args = str_split(addressList[i], ";");
							int from = std::stoi(for_args[0]);
							int to = std::stoi(for_args[1]);

							char oper = for_args[2].front();
							for_args[2].erase(0,1);
							int step = std::stoi(for_args[2]);
							bool notInvert = true;
							if (for_args.size() == 4) {
								notInvert = false;
							}

							switch (oper)
							{
							case '+':
								for (int i = from; i < to; i += step) {
									if (notInvert) {
										currGate.gateAddress.push_back(i);
										currGate.notInverted.push_back(true);
									}
									else {
										currGate.gateAddress.push_back(i);
										currGate.notInverted.push_back(false);
									}
								}
								break;
							case '-':
								for (int i = from; i > to; i -= step) {
									if (notInvert) {
										currGate.gateAddress.push_back(i);
										currGate.notInverted.push_back(true);
									}
									else {
										currGate.gateAddress.push_back(i);
										currGate.notInverted.push_back(false);
									}
								}
								break;
							case '*':
								for (int i = from; i < to; i *= step) {
									if (notInvert) {
										currGate.gateAddress.push_back(i);
										currGate.notInverted.push_back(true);
									}
									else {
										currGate.gateAddress.push_back(i);
										currGate.notInverted.push_back(false);
									}
								}
								break;
							case '/':
								for (int i = from; i > to; i /= step) {
									if (notInvert) {
										currGate.gateAddress.push_back(i);
										currGate.notInverted.push_back(true);
									}
									else {
										currGate.gateAddress.push_back(i);
										currGate.notInverted.push_back(false);
									}
								}
								break;
							default:
								std::cout << "wrong operator";
								break;
							}


						}
						else if (addressList[i].front() == '!') {
							addressList[i].erase(0,1);
							currGate.gateAddress.push_back(std::stoi(addressList[i]));
							currGate.notInverted.push_back(false);
						}
						else {
							currGate.gateAddress.push_back(std::stoi(addressList[i]));
							currGate.notInverted.push_back(true);
						}
					}
					//END

				}
			}
			//WriteTextGate(currGate);
			textGateList.push_back(currGate);
			stateMachine.push_back(FromTextGateToGate(currGate,stateMachine,inputList,outputList,inputWeightList,outputWeightList));
		}
		//END OF WHILE

		for (int i = 0; i < stateMachine.size(); i++) {
			stateMachine[i].connection = SetConnection(textGateList[i], stateMachine);
		}

		myfile.close();
	}
}


Gate FromTextGateToGate(TextGate tGate, std::vector<Gate> &stateMachine, std::vector<std::string> &inputList, std::vector<std::string> &outputList, std::vector<int> &inputWeightList, std::vector<int> &outputWeightList) {
	/*
	std::vector<bool*> connectionList,
	std::vector<bool> notList ,
	bool Reverse=false,
	std::string input="0",
	std::string *inputAddress=NULL,
	std::string output="0",
	std::string *outputAddress=NULL,
	int *weightAddress = NULL,
	int weight = 0
	*/

	std::vector<bool> notList;
	for (int i = 0; i < tGate.notInverted.size(); i++) {
		notList.push_back(tGate.notInverted[i]);
	}

	bool reverse = !tGate.notInvert;

	std::string inputValue = tGate.inValue;
	std::string outputValue = tGate.outValue;

	std::string *inAddress, *outAddress;
	if (tGate.inAddress == -1)
		inAddress = NULL;
	else {
		if (tGate.inPoint == 'i') {
			inAddress = &inputList[tGate.inAddress];
		}
		else {
			inAddress = &outputList[tGate.inAddress];
		}
	}

	if (tGate.outAddress == -1)
		outAddress = NULL;
	else {
		if (tGate.outPoint == 'i') {
			outAddress = &inputList[tGate.outAddress];
		}
		else {
			outAddress = &outputList[tGate.outAddress];
		}
	}

	int weight = tGate.weight;

	int *weightAddress = NULL;


	if (tGate.outAddress == -1)
		weightAddress = NULL;
	else
		if ((tGate.outPoint == 'i')) {
			weightAddress = &inputWeightList[tGate.outAddress];
		}
		else {
			weightAddress = &outputWeightList[tGate.outAddress];
		}
		Gate g =Gate(tGate.id, notList, reverse, inputValue, inAddress, outputValue, outAddress, weightAddress, weight);



		return g;




}


std::vector<bool*> SetConnection( TextGate tGate, std::vector<Gate>&stateMachine) {
	std::vector<bool*> connectionList;
	for (int i = 0; i < tGate.gateAddress.size(); i++) {

		connectionList.push_back(&stateMachine[tGate.gateAddress[i]].active);
	}
	return connectionList;
}
void WriteTextGate(TextGate gate) {
	/*
	int id;
	bool notInvert=true;

	int weight = 0;
	int outAddress = 0, inAddress = 0;
	std::string outValue="", inValue="";
	char outPoint='o', inPoint='i';

	std::vector<int> gateAddress;
	std::vector<bool> notInverted;
	*/
	std::cout << "\n\n ID: " << gate.id;
	std::cout << "\n notInvert: " << gate.notInvert;
	std::cout << "\n weight: " << gate.weight;

	if (gate.outAddress != -1)
		std::cout << "\n outAddress: " << gate.outAddress << ", outValue: " << gate.outValue << ", outPoint: " << gate.outPoint;

	if (gate.inAddress != -1)
		std::cout << "\n inAddress: " << gate.inAddress << ", inValue: " << gate.inValue << ", inPoint: " << gate.inPoint;

	
	if (gate.gateAddress.size() != 0)
	{
		std::cout << "\n Gates: ";
		for (int i = 0; i < gate.gateAddress.size(); i++) {

			if (gate.notInverted[i])
				std::cout << gate.gateAddress[i] << ", ";
			else
				std::cout << "!" << gate.gateAddress[i] << ", ";
		}
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
	for (int i = 0; i < ret.size(); i++) {
	}
	return ret;
}



