//
// Created by Cooki on 12/13/2019.
//

#ifndef SICXE_ASSEMBLER_H
#define SICXE_ASSEMBLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>

#include "command.h"

using namespace std;

struct opElement {
	int format;
	int machineCode;
};

static unordered_map<string, opElement> opTable;
static bool isOpTableInit = false;
void initOpTable();

class Assembler {
	ifstream inputFile;
	ofstream outputFile;
	string inputFileName;
	string outputFileName;
	vector<Command> commands;
	unordered_map<string, int> symbolsTable;
	int length = 0;

	void parse();
	void clear();
public:
	Assembler() = default;
	Assembler(const string& inputFileName, const string& outputFileName);
	void printCommands();
	void printSymbolsTable();
	void pass1();
	void pass2();
//	~Assembler();
};

#endif //SICXE_ASSEMBLER_H
