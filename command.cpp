//
// Created by Cooki on 12/13/2019.
//

#include <iomanip>
#include "command.h"

Command::Command(string line) {
	stringstream ss(line);
	if(line.empty())		// check if the string is empty
		return;
	if(!isblank(line[0]))	// check if the label field exists
		ss >> label;
	ss >> mnemonic >> operand;
	if(!mnemonic.empty() && mnemonic[0] == '+') {
		plus = true;
		mnemonic.erase(mnemonic.begin());
	}
	if(!operand.empty()) {
		int len = operand.size();
		char ch = operand[0];
		if(ch == '#' || ch == '@') {
			flag = ch;
			operand.erase(operand.begin());
		}
		else if(len >= 3 && operand.substr(len - 2, 2) == ",X") {
			flag = 'X';
			operand = operand.substr(0, len-2);
		}
	}
}

const string &Command::getLabel() const {
	return label;
}

const string &Command::getMnemonic() const {
	return mnemonic;
}

const string &Command::getOperand() const {
	return operand;
}

bool Command::isPlus() const {
	return plus;
}

char Command::getFlag() const {
	return flag;
}

string Command::str() const {
	stringstream ss;
	ss << setw(8) << label << " | "
	   << setw(8) << mnemonic << " | "
	   << setw(8) << operand << " | "
	   << ( (plus) ? '+' : ' ' ) << " | "
	   << flag;

	return ss.str();
}
