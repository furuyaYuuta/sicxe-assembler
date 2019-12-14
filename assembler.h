//
// Created by Cooki on 12/13/2019.
//

#ifndef SICXE_ASSEMBLER_H
#define SICXE_ASSEMBLER_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

#include "command.h"

using namespace std;

struct opElement {
	int format;
	int machineCode;
};

static unordered_map<string, opElement> opTable {
	{   "ADD",  { 3,  0x18 } },
	{   "AND",  { 3,  0x40 } },
	{  "COMP",  { 3,  0x28 } },
	{   "DIV",  { 3,  0x24 } },
	{     "J",  { 3,  0x3C } },
	{   "JEQ",  { 3,  0x30 } },
	{   "JGT",  { 3,  0x34 } },
	{   "JLT",  { 3,  0x38 } },
	{  "JSUB",  { 3,  0x48 } },
	{   "LDA",  { 3,  0x00 } },
	{  "LDCH",  { 3,  0x50 } },
	{   "LDL",  { 3,  0x08 } },
	{   "LDX",  { 3,  0x04 } },
	{   "MUL",  { 3,  0x20 } },
	{    "OR",  { 3,  0x44 } },
	{    "RD",  { 3,  0xD8 } },
	{  "RSUB",  { 3,  0x4C } },
	{   "STA",  { 3,  0x0C } },
	{  "STCH",  { 3,  0x54 } },
	{   "STL",  { 3,  0x14 } },
	{  "STSW",  { 3,  0xE8 } },
	{   "STX",  { 3,  0x10 } },
	{    "TD",  { 3,  0xE0 } },
	{   "SUB",  { 3,  0x1C } },
	{   "TIX",  { 3,  0x2C } },
	{    "WD",  { 3,  0xDC } },
	{   "LDB",  { 3,  0x68 } },
	{   "LDT",  { 3,  0x74 } },
	{ "COMPR",  { 2,  0xA0 } },
	{  "TIXR",  { 2,  0xB8 } },
	{ "CLEAR",  { 2,  0xB4 } },
};

class Assembler {
	ifstream inputFile;
	ofstream outputFile;
	string inputFileName;
	string outputFileName;
	vector<Command> commands;
	void parse();
public:
	Assembler() = default;
	Assembler(const string& inputFileName, const string& outputFileName);
};

#endif //SICXE_ASSEMBLER_H
