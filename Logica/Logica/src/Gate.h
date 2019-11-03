#include <vector>
#include<string>
#pragma once
class Gate
{

public:
	Gate();
	Gate(std::string input, std::string *inputAddress, std::string output, std::string *outputAddress, std::vector<bool*> connectionList, int *weightAddress = NULL, int weight = 0);

	~Gate();

	bool active;
	std::string inputValue = "0"; 
	std::string outputValue = "0";
	int weight=0; //if weight is less then number alredy in list output is ignored
	std::vector<bool*> connection;
	std::string zz = "zz";

	void ResetActive();
	void Activate(bool shouldPrint=false);



private:
	bool preActive;
	int* weightAddress;
	std::string *outputAddress = NULL;
	std::string *inputAddress = NULL;

	bool CheckActive();
};

