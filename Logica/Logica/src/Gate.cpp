#include "Gate.h"
#include<iostream>



Gate::Gate()
{
}


Gate::~Gate()
{
}
Gate::Gate(std::string input, std::string *inputAddress, std::string output, std::string *outputAddress, std::vector<bool*> connectionList, int *weightAddress,int  weight)
{

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
		preActive = true;
		return true;
	}
	else if (!connection.empty()) {
		for (std::vector<bool*>::iterator it = connection.begin(); it != connection.end(); ++it) {
			if ((**it) == false) {
				preActive=false;
				return false;

			}
			else if ((**it) == true) {

				if (*it == connection.back()) {
					preActive=true;
					return true;
				}
			}


		}
	}
	else {
		preActive = false;
		return false;
	}

}


