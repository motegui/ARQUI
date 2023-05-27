#include <stdint.h>
#include <user_syscalls.h>
#include <user_lib.h>

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