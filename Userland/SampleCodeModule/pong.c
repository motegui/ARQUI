#include <stdint.h>
#include <stdlib.h>
#include <pong.h>
#include <functions.h>
#include <user_syscalls.h>
#include <stdbool.h>

#define ESC 27
#define X 0
#define Y 1
#define WIDTH 2
#define HEIGHT 3
#define RADIO 2


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



void drawBar(int * bar){
    drawRectangle(bar[X], bar[Y], bar[WIDTH], bar[HEIGHT], WHITE);
}

void moveUpBar(int * bar){
    int move=0;
    for(move=0; bar[Y]-move>top+1 && move<=15; move++){}

    drawRectangle(bar[X], bar[Y] + bar[HEIGHT] - move, bar[WIDTH], move, BLACK);
    bar[Y]=bar[Y]-move;
    drawBar(bar);

}

void moveDownBar(int * bar){
    int move = 0;
    for(move=0; bar[Y]+bar[HEIGHT]+move<bottom && move<=15; move++){}
    drawRectangle(bar[X], bar[Y], bar[WIDTH], move, BLACK);
    bar[Y]=bar[Y]+move;
    drawBar(bar);

}

//chatgpt
void drawBall(int *circle, int color) {
    int x = circle[X];
    int y = circle[Y];
    int r = circle[RADIO];

    for (int i = -r; i <= r; i++) {
        for (int j = -r; j <= r; j++) {
            if (i * i + j * j <= r * r) {
                sys_put_pixel(color, x + i, y + j);
            }
        }
    }
}

void moveBall(int * ball, int x, int y){
    drawBall(ball, BLACK);
    ball[X]=ball[X]+x;
    ball[Y]=ball[Y]+y;
    drawBall(ball, WHITE);
    drawDottedLine(widthScreen/2, top, bottom-top, 4);
}

//izquierda es false, derecha es true
void nextMoveBall(int ball[], int lastDir[], int bar[], bool side){
    int cuadrant=bar[HEIGHT]/10;
    int j=1;
    if(side){
        j=-1;
    }
    if(ball[Y]<bar[Y]+cuadrant){
        lastDir[X]=j*17;
        lastDir[Y]=-15;
    }
    else if(ball[Y]<bar[Y]+2*cuadrant){
        lastDir[X]=j*17;
        lastDir[Y]=-12;
    }
    else if(ball[Y]<bar[Y]+3*cuadrant){
        lastDir[X]=j*17;
        lastDir[Y]=-10;
    }
    else if(ball[Y]<bar[Y]+4*cuadrant){
        lastDir[X]=j*17;
        lastDir[Y]=-5;
    }
    else if(ball[Y]<bar[Y]+5*cuadrant){
        lastDir[X]=j*17;
        lastDir[Y]=-3;
    }
    else if(ball[Y]<bar[Y]+6*cuadrant){
        lastDir[X]=j*17;
        lastDir[Y]=3;
    }
    else if(ball[Y]<bar[Y]+7*cuadrant){
        lastDir[X]=j*17;
        lastDir[Y]=5;
    }
    else if(ball[Y]<bar[Y]+9*cuadrant){
        lastDir[X]=j*17;
        lastDir[Y]=10;
    }
    else if(ball[Y]<bar[Y]+9*cuadrant){
        lastDir[X]=j*7;
        lastDir[Y]=12;
    }
    else{
        lastDir[X]=j*17;
        lastDir[Y]=15;
    }
}



void pong(){
    char key;
    sys_clear_screen();
    //int widthScreen;
    sys_get_screen_width(&widthScreen);
    height = 500;
    width = 900;
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
            int lastDir[2];

            barL[X]=left+20;
            barL[Y]=top+100;
            barL[WIDTH]=10;
            barL[HEIGHT]=100;

            barR[X]=right-30;
            barR[Y]=top+100;
            barR[WIDTH]=10;
            barR[HEIGHT]=100;

            ball[X]=widthScreen/2;
            ball[Y]=(bottom-top)/2;
            ball[RADIO]=10;

            lastDir[X]=20;
            lastDir[Y]=0;


            drawBar(barL);
            drawBar(barR);
            drawBall(ball, WHITE);
            while(1){
                sys_get_ticks(1);
                key=getKey();
                if(key=='W'){
                    moveUpBar(barL);
                    sys_get_clean_buffer();

                }
                if(key=='S'){
                    moveDownBar(barL);
                    sys_get_clean_buffer();

                }
                if(key=='O'){
                    moveUpBar(barR);
                    sys_get_clean_buffer();

                }
                if(key=='L'){
                    moveDownBar(barR);
                    sys_get_clean_buffer();

                }
                if(key==ESC){
                    sys_clear_screen();
                    return;
                }
                if(ball[Y]-ball[RADIO]+lastDir[Y]<top+1){
                    lastDir[Y]=-lastDir[Y];
                }

                if(ball[Y]+ball[RADIO]+lastDir[Y]>bottom){
                    lastDir[Y]=-lastDir[Y];
                }
                if(ball[X]+ball[RADIO]+lastDir[X]>barR[X]){
                    if(ball[Y]+ball[RADIO]>barR[Y] && ball[Y]-ball[RADIO]<barR[Y]+barR[HEIGHT]){
                        nextMoveBall(ball, lastDir, barR, true);
                        //choca en la barra derecha
                    }
                    else{
                        lastDir[X]=-lastDir[X];
                        lastDir[Y]=-lastDir[Y];
                        drawBall(ball, BLACK);
                        ball[X]=widthScreen/2;
                        ball[Y]=(bottom-top)/2;
                        sys_beep(300,5);
                        sys_get_ticks(30);
                    }

                }
                if(ball[X]-ball[RADIO]+lastDir[X]<barL[X]+barL[WIDTH]){
                    if(ball[Y]+ball[RADIO]>barL[Y] && ball[Y]-ball[RADIO]<barL[Y]+barL[HEIGHT]){
                        nextMoveBall(ball, lastDir, barL, false);
                        //choca en la barra izquierda
                    }
                    else{
                        lastDir[X]=-lastDir[X];
                        lastDir[Y]=-lastDir[Y];
                        drawBall(ball, BLACK);
                        ball[X]=widthScreen/2;
                        ball[Y]=(bottom-top)/2;
                        sys_beep(300,5);
                        sys_get_ticks(30);
                    }

                }


                moveBall(ball, lastDir[X], lastDir[Y]);

            }
        }
    }


}
