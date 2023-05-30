 #include <sys_calls.h>
 #include <stdint.h>
 #include <video.h>
 #include <keyboard_driver.h>
 #include <lib.h>
 #include <getRegs.h>
 #include <stdbool.h>

extern const uint64_t regs[18];
 extern int getHours();
 extern int getMinutes();
 extern int getSeconds();


typedef int64_t (*syscallT) (uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);


void _0_empty(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5){
    clearScreen();
 }

 void _1_write(uint64_t c, uint64_t color, uint64_t r3, uint64_t r4, uint64_t r5){
    putArrayNext( (char *) c, color);
}

 void _2_read(uint64_t buffer, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5){
     ((char*) buffer)[0] = nextElement();
}

void _3_getHours(uint64_t hours, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5){
    *((int*) hours) =  getHours();

}

void _4_getMinutes(uint64_t min, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5){
    *((int*) min) =  getMinutes();
}

void _5_getSeconds(uint64_t seconds, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5){
    *((int*) seconds) =  getSeconds();
}

void _6_newLine(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5){
    putLine();
}

void _7_write_dec(uint64_t c, uint64_t color, uint64_t r3, uint64_t r4, uint64_t r5){
    putDecNext( (int) c, color);
}

void _8_save_registers(uint64_t registers, uint64_t isSaved, uint64_t r3, uint64_t r4, uint64_t r5){
    if(!isRegsSaved()){
        (*(bool *) isSaved)= false;
        return;
    }
    (*(bool *) isSaved)= true;
    for(int i = 0; i<18; i++){
            ((uint64_t *) registers)[i] = regs[i];
        }
}

static syscallT syscalls[]  = {
    (syscallT) _0_empty, 
    (syscallT) _1_write, 
    (syscallT) _2_read, 
    (syscallT) _3_getHours, 
    (syscallT) _4_getMinutes, 
    (syscallT) _5_getSeconds,
    (syscallT) _6_newLine, 
    (syscallT) _7_write_dec,
    (syscallT) _8_save_registers
};

int64_t sysDispatcher(uint64_t syscall, uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4, uint64_t r5){
    return syscalls[syscall](r1, r2, r3, r4, r5);
}


