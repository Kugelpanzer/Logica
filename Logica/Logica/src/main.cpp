#include<iostream>
#include"Parser.h"

using namespace std;



int main() {
	
	vector<Gate> scheme;
	vector<string> input, output;
	vector<int>inWeight, outWeight;
	for (int i = 0; i < 2; i++) {
		input.push_back("");
		output.push_back("");
		inWeight.push_back(0);
		outWeight.push_back(0);
	}
	parse_file("xor", scheme, input, output, inWeight, outWeight);
	int a;
	cin >> a;
	return 1;
}

void Pulse(vector<Gate> &stateMachine) {
	for (int i = 0; i < stateMachine.size(); i++) {
		stateMachine[i].Activate();
	}
	for (int i = 0; i < stateMachine.size(); i++) {
		stateMachine[i].ResetActive();
	}

}