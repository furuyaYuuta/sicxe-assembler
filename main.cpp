
#include <iostream>
#include "assembler.h"

using namespace std;

int main() {
    Assembler assembler("in.txt", "out.txt");
	assembler.pass1();
	assembler.printCommands();
	assembler.printSymbolsTable();
    return 0;
}