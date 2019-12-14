//
// Created by Cooki on 12/13/2019.
//

#include "assembler.h"

Assembler::Assembler(const string& inputFileName, const string& outputFileName) {
	this->inputFileName = inputFileName;
	this->outputFileName = outputFileName;
	inputFile.open(inputFileName);
	if(inputFile.fail()) {
		cerr << "Error: the file " << inputFileName << "cannot be opened\n";
		return;
	} else parse();
}

void Assembler::parse() {
	string line;
	while(getline(inputFile, line)) {
		if(!line.empty())
			commands.emplace_back(Command(line));
		cerr << commands.back().str() << endl;
	}
}
