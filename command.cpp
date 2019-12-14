//
// Created by Cooki on 12/13/2019.
//

#include <iomanip>
#include <regex>
#include "command.h"

Command::Command(string line) {
	stringstream ss(line);
	if(line.empty())		// check if the string is empty
		return;
	else if(line[0] == '.') {	// check if the line is comment
		comment = true;
		return;
	}
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
	if(comment)
		ss << "This is a comment line.";
	else {
		ss << setw(8) << label << " | "
		   << setw(8) << mnemonic << " | "
		   << setw(8) << operand << " | "
		   << ( (plus) ? '+' : ' ' ) << " | "
		   << flag << " | "
		   << getDecimalOperand();
	}

	return ss.str();
}

bool Command::isComment() const {
	return comment;
}

bool isNumber(const string &str) {
	return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

int Command::getDecimalOperand() const {
	static regex r(R"(([XC])\'([\da-dA-D\w]+)\')");
	smatch match;
	if(regex_match(operand, match, r)) {
		char type = match[1].str()[0];
		string val = match[2].str();
		if(type == 'X')
			return stoi(val, nullptr, 16);
		else if(type == 'C') {
			unsigned int bin = 0;
			for(const auto& ch : val)
				bin = (bin << (4*2)) + ch;
			return (int)bin;
		}
	}
	return (isNumber(operand)) ? stoi(operand) : -1;
}

int Command::getCharLength() const {
	static regex r(R"(C\'([\da-dA-D\w]+)\')");
	static smatch match;
	if(regex_match(operand, match, r))
		return match[1].str().length();
	return 1;
}
