#include <stdint.h>
#include "video.h"

#define REGISTERS_QTY 15

void zeroException();
void invalidOpException();
extern uint64_t * getRegs();


uint64_t exceptionDispatcher(void * excepCode){
    switch((uint64_t)excepCode){
        case 0:
            zeroException(); 
            break;
		case 6:
			invalidOpException();
			break;
	}
	printError("--REGISTERS AT TIME OF EXCEPTION--");
	char* registers[REGISTERS_QTY] = {"RAX", "RBX", "RCX", "RDX", "RBP", "RDI", "RSI", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15"};
	uint64_t * regs = getRegs();
	for(int i = 0; i < REGISTERS_QTY; i++){
        int j = 0;
		while(registers[i][j] != 0){
			putLetterNext(registers[i][j], WHITE);
			j++;
		}
		putLetterNext(':', WHITE);
		putLetterNext(' ', WHITE);
		putLetterNext(' ', WHITE);
		putLetterNext('0', WHITE);
		putLetterNext('x', WHITE);
		printHexa(regs[i]);
		putLetterNext('\n', WHITE);
	}
	printError("--RESTARTING--");
    return 0;
}

void zeroException(){
    printError("ERROR: DIVIDING BY ZERO");
}

void invalidOpException(){
	printError("ERROR: INVALID OPERATION CODE");
}

