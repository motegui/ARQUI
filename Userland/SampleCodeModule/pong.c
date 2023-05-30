#include <pong.h>
#include <functions.h>
#include <user_syscalls.h>

void drawScreenBorders(int starty, int endy, int startx, int endx){
    for (int x = startx; x<= endx; x++){
        sys_put_pixel(WHITE, x, starty);
        sys_put_pixel(WHITE, x, endy);
    }

    for (int y = starty; y<= endy; y++){
        sys_put_pixel(WHITE, startx, y);
        sys_put_pixel(WHITE, endx, y);
    }
}

void pong(){
    sys_clear_screen();
    int widthScreen;
    sys_get_screen_width(&widthScreen);
    int height = 500;
    int width = 700;
    int top = 5;
    int bottom = top+height;
    int left = (widthScreen-width)/2;
    int right = widthScreen-(widthScreen-width)/2;
    drawScreenBorders(top, bottom, left, right);
}