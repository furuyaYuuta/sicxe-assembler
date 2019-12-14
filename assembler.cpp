//
// Created by Cooki on 12/13/2019.
//

#include <iomanip>
#include <set>
#include "assembler.h"

Assembler::Assembler(const string& inputFileName, const string& outputFileName) {
	if(!isOpTableInit)
		initOpTable();
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
		Command cmd(line);
		if(!line.empty() && !cmd.isComment())
			commands.emplace_back(cmd);
	}
}

void Assembler::pass1() {
	if(commands.empty()) {
		cerr << "Error: There are no commands initialized yet." << endl;
		return;
	}
	// start process psss 1
	auto cmd = commands.begin();
	int startAddress = 0;
	if(cmd->getMnemonic() == "START") {
		startAddress = commands[0].getDecimalOperand();
		cmd++;
	}
	int LOCCTR = startAddress;
	while(cmd != commands.end()) {
		// check the label is whether created or not
		if (symbolsTable.find(cmd->getLabel()) != symbolsTable.end()) {
			cerr << "Error: duplicate definition of " << cmd->getLabel() << endl;
			clear();
			return;
		} else if (!cmd->getLabel().empty()) {
			symbolsTable[cmd->getLabel()] = LOCCTR;
		}

		// check if the opCode is valid and update LOCCTR
		string opCode = cmd->getMnemonic();
		if (opTable.find(opCode) != opTable.end())
			LOCCTR += (cmd->isPlus()) ? 4 : opTable[opCode].format;
		else if (opCode == "WORD")
			LOCCTR += 3;
		else if (opCode == "RESW")
			LOCCTR += 3 * cmd->getDecimalOperand();
		else if (opCode == "RESB")
			LOCCTR += cmd->getDecimalOperand();
		else if (opCode == "BYTE")
			LOCCTR += cmd->getCharLength();
		else if (opCode == "BASE") {

		}
		else if (opCode == "END")
			break;
		else {
			cerr << "Error: Unrecognized opcode " << opCode << endl;
			clear();
			return;
		}
		cmd++;
	}
	length = LOCCTR - startAddress;
}

void Assembler::printCommands() {
	for(const auto& command : commands) {
		cerr << command.str() << endl;
	}
}

void Assembler::clear() {
	symbolsTable.clear();
}

void Assembler::printSymbolsTable() {
	auto compFunc = [](pair<string, int> a, pair<string, int> b) {
		return a.second < b.second;
	};
	vector<pair<string, int>> v(symbolsTable.begin(), symbolsTable.end());
	sort(v.begin(), v.end(), compFunc);
	cerr << hex << setfill('0');
	for(const auto& symbol : v)
		cerr << symbol.first << "\t0x"
			 << setw(4) << symbol.second << endl;
	cerr << dec << setfill(' ');
}

void initOpTable() {
	opTable[  "ADD"] = opElement{ 3,  0x18 };
	opTable[  "AND"] = opElement{ 3,  0x40 };
	opTable[ "COMP"] = opElement{ 3,  0x28 };
	opTable[  "DIV"] = opElement{ 3,  0x24 };
	opTable[    "J"] = opElement{ 3,  0x3C };
	opTable[  "JEQ"] = opElement{ 3,  0x30 };
	opTable[  "JGT"] = opElement{ 3,  0x34 };
	opTable[  "JLT"] = opElement{ 3,  0x38 };
	opTable[ "JSUB"] = opElement{ 3,  0x48 };
	opTable[  "LDA"] = opElement{ 3,  0x00 };
	opTable[ "LDCH"] = opElement{ 3,  0x50 };
	opTable[  "LDL"] = opElement{ 3,  0x08 };
	opTable[  "LDX"] = opElement{ 3,  0x04 };
	opTable[  "MUL"] = opElement{ 3,  0x20 };
	opTable[   "OR"] = opElement{ 3,  0x44 };
	opTable[   "RD"] = opElement{ 3,  0xD8 };
	opTable[ "RSUB"] = opElement{ 3,  0x4C };
	opTable[  "STA"] = opElement{ 3,  0x0C };
	opTable[ "STCH"] = opElement{ 3,  0x54 };
	opTable[  "STL"] = opElement{ 3,  0x14 };
	opTable[ "STSW"] = opElement{ 3,  0xE8 };
	opTable[  "STX"] = opElement{ 3,  0x10 };
	opTable[   "TD"] = opElement{ 3,  0xE0 };
	opTable[  "SUB"] = opElement{ 3,  0x1C };
	opTable[  "TIX"] = opElement{ 3,  0x2C };
	opTable[   "WD"] = opElement{ 3,  0xDC };
	opTable[  "LDB"] = opElement{ 3,  0x68 };
	opTable[  "LDT"] = opElement{ 3,  0x74 };
	opTable["COMPR"] = opElement{ 2,  0xA0 };
	opTable[ "TIXR"] = opElement{ 2,  0xB8 };
	opTable["CLEAR"] = opElement{ 2,  0xB4 };
	isOpTableInit = true;
}
