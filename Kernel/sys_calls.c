#include <sys_calls.h>
#include <stdint.h>
#include <video.h>
#include <keyboard_driver.h>
#include <lib.h>

void _0_empty(uint64_t r1, uint64_t r2, uint64_t r3, uint64_t r4,uint64_t r5){
    ;
}

void _1_write(uint64_t x, uint64_t y, uint64_t c, uint64_t len, uint64_t color){
    draw_string(x, y, (char *) c, len, color, BLACK);
}


void _2_read(uint64_t buffer, uint64_t length, uint64_t r3, uint64_t r4, uint64_t r5){
    ((char*) buffer)[0] = nextElement();


}
