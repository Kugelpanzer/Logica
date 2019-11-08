#include <vector>
#include<string>
#pragma once
class Gate
{

public:
	Gate();
	Gate(std::vector<bool*> connectionList, std::vector<bool> notList ,bool Reverse=false, std::string input="0", std::string *inputAddress=NULL, std::string output="0", std::string *outputAddress=NULL,  int *weightAddress = NULL, int weight = 0);
	Gate(std::vector<bool*> connectionList, std::vector<bool> notList, bool Reverse=false, std::string input = "0", std::string *inputAddress = NULL, int *weightAddress = NULL, int weight = 0);
	Gate(std::vector<bool*> connectionList, std::vector<bool> notList, bool Reverse=false, std::string output = "0", std::string *outputAddress = NULL, int *weightAddress = NULL, int weight = 0);
	Gate(std::vector<bool*> connectionList, std::vector<bool> notList, bool Reverse=false, int *weightAddress = NULL, int weight = 0);

	~Gate();

	bool active;
	std::string inputValue = "0"; 
	std::string outputValue = "0";
	int weight=0; //if weight is less then number alredy in list output is ignored
	std::vector<bool*> connection;

	void ResetActive();
	void Activate(bool shouldPrint=false);



private:
	bool preActive;
	int* weightAddress;
	std::string *outputAddress = NULL;
	std::string *inputAddress = NULL;
	std::vector<bool> notList;
	bool notReverse = true;
	bool CheckActive();
};

