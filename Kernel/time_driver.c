
#include <stdint.h>
#include <time_driver.h>
#include <video.h>
#include <lib.h>
extern int getHours();
extern int getMinutes();
extern int getSeconds();
int getFormat(int n)
{
    // quiero pasarde int a char
    int dec = n % 240;
    dec = dec >> 4;
    int units = n & 15;
    return dec * 10 + units;
}
getTime(uint32_t x, uint32_t y, int color)
{
    putArrayNext("HORA: ", color);
    putDecNext(getHours(), color);
    putArrayNext(":", color);
    putDecNext(getFormat(getMinutes()), color);
    putArrayNext(":", color);
    putDecNext(getFormat(getSeconds()), color);
}
