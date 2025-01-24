//Rishi Govindan
//rigovind
//pa8

#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

int main(int argc, char* argv[]) {
    	if (argc != 3) {
        	return 1;
    	}

	std::ifstream inputFile(argv[1]);
    	std::ofstream outputFile(argv[2]);

	if (!inputFile.is_open()) {
        	return 1;
    	}


	if (!outputFile.is_open()) {
        	return 1;
    	}

	Dictionary d;
    	std::string line;
    	int lineNum = 1;


	while (std::getline(inputFile, line)) {
        	d.setValue(line, lineNum++);
    	}

	outputFile << d.to_string();
	outputFile << d.pre_string();
	inputFile.close();
    	outputFile.close();

	return 0;
}


