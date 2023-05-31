#include <stdint.h>
#include <stdlib.h>
#include <pong.h>
#include <functions.h>
#include <user_syscalls.h>

#define ESC 27
#define X 0
#define Y 1
#define WIDTH 2
#define HEIGHT 3
#define RADIO 2

// struct rectangle{
//     int x;
//     int y;
//     int length;
//     int width;
// };
// typedef struct rectangle * Rectangle;

int widthScreen;
int height;
int width;
int top;
int bottom;
int left;
int right;

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

void drawRectangle(int x, int y, int sizex, int sizey, int color){
    for(int i = 0; i<sizex; i++){
        for(int j=0; j< sizey; j++){
            sys_put_pixel(color, i+x, j+y);
        }
    }
}

void drawDottedLine(int x, int y, int length, int size){
    for(int i=0; i<length; i+=size*2){
        drawRectangle(x-size/2, i+y, size, size, WHITE);
    }
}

// void drawBar(Rectangle bar){
//     drawRectangle(bar->x, bar->y, bar->width, bar->length, WHITE);
// }

// void moveUpBar(Rectangle bar){
//     int move = 5;
//     drawRectangle(bar->x, bar->y + bar->length - move, bar->width, move, BLACK);
//     bar->y=bar->y-5;
//     drawBar(bar);

// }

// void moveDownBar(Rectangle bar){
//     int move = 5;
//     drawRectangle(bar->x, bar->y, bar->width, move, BLACK);
//     bar->y=bar->y+5;
//     drawBar(bar);

// }

void drawBar(int * bar){
    drawRectangle(bar[X], bar[Y], bar[WIDTH], bar[HEIGHT], WHITE);
}

void moveUpBar(int * bar){
    int move=0;
    for(move=0; bar[Y]-move>top+1 && move<=5; move++){}

    drawRectangle(bar[X], bar[Y] + bar[HEIGHT] - move, bar[WIDTH], move, BLACK);
    bar[Y]=bar[Y]-move;
    drawBar(bar);

}

void moveDownBar(int * bar){
    int move = 0;
    for(move=0; bar[Y]+bar[HEIGHT]+move<bottom && move<=5; move++){}
    drawRectangle(bar[X], bar[Y], bar[WIDTH], move, BLACK);
    bar[Y]=bar[Y]+move;
    drawBar(bar);

}

void drawBall(int * circle){
    int radio = circle[RADIO];
    int auxX=circle[X];
    int auxY=circle[Y]-radio;
    for(int i=0; i<=radio; i+=2){
        for(int j=0; j<=i; j++){
            sys_put_pixel(WHITE, auxX+j, auxY);
            sys_put_pixel(WHITE, auxX-j, auxY);
        }
        for(int j=0; j<=i; j++){
            sys_put_pixel(WHITE, auxX+j, auxY);
            sys_put_pixel(WHITE, auxX-j, auxY);
        }
        auxY+=2;
    }

}


void pong(){
    char key;
    sys_clear_screen();
    //int widthScreen;
    sys_get_screen_width(&widthScreen);
    height = 500;
    width = 700;
    top = 5;
    bottom = top + height;
    left = (widthScreen-width)/2;
    right = widthScreen-(widthScreen-width)/2;
    sys_write("Press ENTER to play", WHITE);
    enter();
    sys_write("Press ESC to leave the game at any moment", WHITE);
    while(1){
        key=getKey();
        if(key==ESC){
            sys_clear_screen();
            return;
        }
        if(key=='\n'){
            sys_clear_screen();
            drawScreenBorders(top, bottom, left, right);
            drawDottedLine(widthScreen/2, top, bottom-top, 4);
            int barL[4]; //={left+20, top+100, 10, 50};
            int barR[4]; //={right-30, top+100, 10, 50};
            int ball[3];

            barL[X]=left+20;
            barL[Y]=top+100;
            barL[WIDTH]=10;
            barL[HEIGHT]=50;

            barR[X]=right-30;
            barR[Y]=top+100;
            barR[WIDTH]=10;
            barR[HEIGHT]=50;

            ball[X]=100;
            ball[Y]=(bottom-top)/2;
            ball[RADIO]=5;
            
            // Rectangle barR;
            // Rectangle barL;
            // barL->x=left+20;
            // barL->y=top+100;
            // barL->width=10;
            // barL->length=50;
            // barR->x=right-30;
            // barR->y=top+100;
            // barR->width=10;
            // barR->length=50;
            drawBar(barL);
            drawBar(barR);
            drawBall(ball);
            while(1){
                key=getKey();
                if(key=='W'){
                    moveUpBar(barL);
                }
                if(key=='S'){
                    moveDownBar(barL);
                }
                if(key=='O'){
                    moveUpBar(barR);
                }
                if(key=='L'){
                    moveDownBar(barR);
                }
                if(key==ESC){
                    sys_clear_screen();
            return;
                }
            }
        }
    }


}