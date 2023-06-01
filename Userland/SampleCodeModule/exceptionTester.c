#include "exceptionTester.h"
extern void divzerotester();
extern void opcodetester();

void divisionTester(){
        printLine("Dividing by zero..");
		divzerotester();
}

void invalidOpTester(){
        printLine("Invalid Operation..");
		opcodetester();
}