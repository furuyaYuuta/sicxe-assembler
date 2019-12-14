
#include <iostream>
#include "assembler.h"

using namespace std;

int main() {
    Assembler assembler("in.txt", "out.txt");
    assembler.printCommands();
	assembler.pass1();
    return 0;
}