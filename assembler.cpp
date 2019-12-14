//
// Created by Cooki on 12/13/2019.
//

#include "assembler.h"

Assembler::Assembler(const string& inputFileName, const string& outputFileName) {
	inputFile.open(inputFileName);
	if(inputFile.fail()) {
		cerr << "Error: the file " << inputFileName << "cannot be opened\n";
		return;
	} else parse();
	this->inputFileName = inputFileName;
	this->outputFileName = outputFileName;
}

void Assembler::parse() {
	string line;
	while(getline(inputFile, line)) {
		if(!line.empty())
			commands.emplace_back(Command(line));
	}
}

void Assembler::pass1() {
	if(commands.empty()) {
		cerr << "Error: There are no commands initialized yet." << endl;
		return;
	}
	// start process psss 1
	auto curCmd = commands.begin();
	int LOCCTR = 0;
	if(curCmd->getMnemonic() == "start") {
		LOCCTR = stoi(commands[0].getOperand());
		curCmd++;
	}
	while(curCmd != commands.end()) {

		curCmd++;
	}
}

void Assembler::printCommands() {
	for(const auto& command : commands) {
		cerr << command.str() << endl;
	}
}

