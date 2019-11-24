#include "Gate.h"
#include<iostream>



Gate::Gate()
{
}


Gate::~Gate()
{
}
Gate::Gate(int id, std::vector<bool> notList, bool Reverse, std::string input , std::string *inputAddress , std::string output , std::string *outputAddress , int *weightAddress , int weight )
{
	this->id = id;
	this->notList = notList;
	this->inputValue = input;
	this->inputAddress = inputAddress;
	this->outputValue = output;
	this->outputAddress = outputAddress;
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

			//break
			if ((**it) != notList[br]) {
				preActive= !notReverse;
				return !notReverse;

			}
			else if ((**it) == notList[br]) {

				if (*it == connection.back()) {

					//FOR TEST ONLY

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


