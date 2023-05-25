#include <stdint.h>
#include <user_syscalls.h>
#include <userLib.h>

void sys_clear_screen() {
    sys_int_80((uint64_t)0, 0, 0, 0, 0, 0);
}

void sys_write(char * c, int color) {
    sys_int_80((uint64_t)1,(uint64_t) c,color,0,0, 0);
}

void sys_read( char * buff){
    sys_int_80((uint64_t)2,(uint64_t)buff,0, 0, 0, 0);
} 

void sys_get_hours(int * hours){
    sys_int_80((uint64_t)3, (uint64_t)hours, 0, 0, 0, 0);
}

void sys_get_minutes(int * min){
    sys_int_80((uint64_t)4, (uint64_t)min, 0, 0, 0, 0);
}

void sys_get_seconds(int * sec){
    sys_int_80((uint64_t)5, (uint64_t)sec, 0, 0, 0,0);
}

void enter(){
    sys_int_80((uint64_t)6, 0, 0, 0, 0, 0);
}

void sys_write_dec(int c, int color) {
    sys_int_80((uint64_t)7,(uint64_t) c,color,0,0, 0);
}

// void sys_beep(int freq, int time){
//     sys_int_80((uint64_t)10,(uint64_t)freq,(uint64_t)time,0,0,0);
// }

// void sys_get_mem(int memoryPos, unsigned char * buff) {
//     sys_int_80((uint64_t)12, (uint64_t)memoryPos, (uint64_t)buff, 0, 0, 0);
// }

// void sys_get_regs(int * captured, int * regs) {
//     sys_int_80((uint64_t)13, (uint64_t)captured, (uint64_t) regs, 0, 0, 0);
// }