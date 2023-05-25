#include <stdint.h>
void sys_clear_screen();

void sys_write(char * c, int color);

void sys_read( char * buff);

void sys_get_hours(int * hours);

void sys_get_minutes(int * min);

void sys_get_seconds(int * sec);

void sys_write_dec(int c, int color);

void enter();