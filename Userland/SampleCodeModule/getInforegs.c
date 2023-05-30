#include <stdbool.h>
#include <user_syscalls.h>
#include <functions.h>
#include "getInforegs.h"


void getRegInfo() {
    uint64_t registers[18];
    bool isSaved;
    sys_registers(registers, &isSaved);
    if(!isSaved){
        print("Registers not saved");
    }
    else{
        print("-- REGISTER VALUES --\n");
        enter();
        const char *registersO[] = {"RAX", "RBX", "RCX", "RDX", "RBP", "RDI", "RSI", "R8 ", "R9 " , "R10", "R11", "R12", "R13", "R14", "R15"};
        for (int i = 0; i < 15; i++) {
        print(registersO[i]);
        print(": 0x");
        printHexa(registers[i]);
        enter();
    }
    }
    
    
}