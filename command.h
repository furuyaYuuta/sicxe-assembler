//
// Created by Cooki on 12/13/2019.
//

#ifndef SICXE_COMMAND_H
#define SICXE_COMMAND_H

#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Command {
	string label;
	string mnemonic;
	string operand;
	bool comment = false;
	bool plus = false;
	char flag = 0;
public:
	Command() = default;
	explicit Command(string line);

	const string &getLabel() const;

	const string &getMnemonic() const;

	const string &getOperand() const;

	bool isPlus() const;

	char getFlag() const;

	string str() const;
};

#endif //SICXE_COMMAND_H
