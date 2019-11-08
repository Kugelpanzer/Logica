#include "Gate.h"
#include<iostream>



Gate::Gate()
{
}


Gate::~Gate()
{
}
Gate::Gate(std::vector<bool*> connectionList, std::vector<bool> notList, bool Reverse = false, std::string input = "0", std::string *inputAddress = NULL, std::string output = "0", std::string *outputAddress = NULL, int *weightAddress = NULL, int weight = 0)
{

	this->connection = connectionList;
	this->notList = notList;
	this->inputValue = input;
	this->inputAddress = inputAddress;
	this->outputValue = output;
	this->outputAddress = outputAddress;
	this->weightAddress = weightAddress;
	this->weight = weight;
	this->notReverse = !Reverse;
}
Gate::Gate(std::vector<bool*> connectionList, std::vector<bool> notList, bool Reverse = false, std::string input = "0", std::string *inputAddress = NULL, int *weightAddress = NULL, int weight = 0) {
	this->connection = connectionList;
	this->notList = notList;
	this->inputValue = input;
	this->inputAddress = inputAddress;
	this->weightAddress = weightAddress;
	this->weight = weight;
	this->notReverse = !Reverse;

}
Gate::Gate(std::vector<bool*> connectionList, std::vector<bool> notList, bool Reverse = false, std::string output = "0", std::string *outputAddress = NULL, int *weightAddress = NULL, int weight = 0) {
	this->connection = connectionList;
	this->notList = notList;
	this->outputValue = output;
	this->outputAddress = outputAddress;
	this->weightAddress = weightAddress;
	this->weight = weight;
	this->notReverse = !Reverse;
}
Gate::Gate(std::vector<bool*> connectionList, std::vector<bool> notList, bool Reverse = false, int *weightAddress = NULL, int weight = 0) {
	this->connection = connectionList;
	this->notList = notList;
	this->weightAddress = weightAddress;
	this->weight = weight;
	this->notReverse = !Reverse;

}



void Gate::Activate(bool shouldPrint) {
	if (CheckActive()) {
		if ((outputAddress != NULL) && (weight >= *weightAddress))
			*outputAddress = outputValue;
		if (shouldPrint) {
			std::cout << outputValue;
		}
	}
}

void Gate::ResetActive() {
	active = preActive;
	preActive = false; 
}

bool Gate::CheckActive() {
	if ((inputAddress != NULL) && (inputValue == *inputAddress)) {
		preActive = notReverse;
		return notReverse;
	}
	else if (!connection.empty()) {
		int br = 0;
		for (std::vector<bool*>::iterator it = connection.begin(); it != connection.end(); ++it) {

			if ((**it) == !notList[br]) {
				preActive= !notReverse;
				return !notReverse;

			}
			else if ((**it) == notList[br]) {

				if (*it == connection.back()) {
					preActive= notReverse;
					return notReverse;
				}
			}
		br++;
		}
	}
	else {
		preActive = notReverse;
		return notReverse;
	}

}


