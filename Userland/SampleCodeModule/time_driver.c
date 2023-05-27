
#include <stdint.h>
#include <time_driver.h>
#include <user_syscalls.h>

int getFormat(int n)
{
    // quiero pasarde int a char
    int dec = n % 240;
    dec = dec >> 4;
    int units = n & 15;
    return dec * 10 + units;
}
 void getTime(int color)
{
    sys_write("HORA: ", color);
    int hours, minutes, seconds;
    sys_get_hours(&hours);
    sys_get_minutes(&minutes);
    sys_get_seconds(&seconds);
    sys_write_dec(getFormat(hours), color);
    sys_write(":", color);
    sys_write_dec(getFormat(minutes), color);
    sys_write(":", color);
    sys_write_dec(getFormat(seconds), color);
}
