#include <stdint.h>
#include <functions.h>
#include <user_syscalls.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>

#define V 21
#define H 65
#define N 100
#define ESC 27

typedef struct
{
    int x, y;            // Position (coordinates X,Y)
    int ModX, ModY;      // Modification
    char imagen;
} snk;

typedef struct
{
    int x, y;
} frt;

snk snakebody[N]; // Array of structs for the body of the snake
frt fruit;
int fruitEaten = 0; // Flag to check if the fruit has been eaten

void Intro_Field(char campo[V][H]);
void Intro_Data(char campo[V][H], int tam);
void draw(char campo[V][H]);
void init(int *tam, char campo[V][H]);
void loop(char campo[V][H], int tam);
int input(char campo[V][H], int *tam, int *muerto);
void update(char campo[V][H], int tam);
void Intro_Data2(char campo[V][H], int tam);
int checkOverlap(int x, int y, snk *snake, int tam);

int checkOverlap(int x, int y, snk *snake, int tam) {
    for (int i = 0; i < tam; i++) {
        if (snake[i].x == x && snake[i].y == y) {
            return 1; // Overlap exists
        }
    }
    return 0; // There is not overlap
}

void init(int *tam, char campo[V][H]) {
    // Snake's head inizialitation
    snakebody[0].x = 32;
    snakebody[0].y = 10;

    // Snake size
    *tam = 4;

    // Fruit coordinates
    srand(getSeconds()); // Seed
    fruit.x = rand() % (H - 2) + 1;
    fruit.y = rand() % (V - 2) + 1;

    for (int i = 0; i < *tam; i++) {
        snakebody[i].ModX = 1;
        snakebody[i].ModY = 0;
    }

    Intro_Field(campo);
    Intro_Data(campo, *tam);
}

void Intro_Field(char campo[V][H]) {
    int i, j;
    for (i = 0; i < V; i++) {
        for (j = 0; j < H; j++) {
            if (i == 0 || i == V - 1) {
                campo[i][j] = '-';
            } else if (j == 0 || j == H - 1) {
                campo[i][j] = '|';
            } else {
                campo[i][j] = ' ';
            }
        }
    }
}

void Intro_Data(char campo[V][H], int tam) {
    int i;

    for (i = 1; i < tam; i++) {
        snakebody[i].x =  snakebody[i - 1].x  - 1;
        snakebody[i].y =  snakebody[i - 1].y;
        snakebody[i].imagen = 'X';
    }
    snakebody[0].imagen = 'O';

    for (i = 0; i < tam; i++) {
        campo[snakebody[i].y][snakebody[i].x] = snakebody[i].imagen;
    }
    campo[fruit.y][fruit.x] = 'a';
}

void draw(char campo[V][H]) {
    int i, j;
    for (i = 0; i < V; i++) {
        for (j = 0; j < H; j++) {
            printChar(campo[i][j], PINK);
        }
        enter();
    }
}

void loop(char campo[V][H], int tam) {
    int muerto = 0;

    do {
        sys_clear_screen();
        draw(campo);

        if(input(campo, &tam, &muerto) == -1){
            return;
        }

        update(campo, tam);
        sys_sleep(80); // This will pause the program during 100 ms (0.1 seconds)

    } while (muerto == 0);
    if(muerto == 1){
        sys_beep(300,5);

        sys_write("You lose. Coming back to the main menu", RED);
        enter();
    }
}

int input(char campo[V][H], int *tam, int *muerto) {
    char key;

    // Check if the snake is dead
    if (snakebody[0].x == 0 || snakebody[0].x == H - 1 || snakebody[0].y == 0 || snakebody[0].y == V - 1) {
        *muerto = 1;
    }
    for (int i = 1; i < *tam; i++) {
        if (snakebody[0].x == snakebody[i].x && snakebody[0].y == snakebody[i].y) {
            *muerto = 1;
        }
    }

    // Check if the fruit has been eaten
    if (snakebody[0].x == fruit.x && snakebody[0].y == fruit.y) {
        if (!fruitEaten) { // If the fruit has not been eaten
            *tam += 1;
            snakebody[*tam - 1].imagen = 'X';
            fruitEaten = 1; // Turn on the flag
        }
    } else {
        fruitEaten = 0; // Reestablish the flag
    }

    if (*muerto == 0) {
        key = getKey();
        //sys_sleep(1);
        if (key == 'S' && snakebody[0].ModY != -1) {
            snakebody[0].ModX = 0;
            snakebody[0].ModY = 1;
        }
        if (key == 'W' && snakebody[0].ModY != 1) {
            snakebody[0].ModX = 0;
            snakebody[0].ModY = -1;
        }
        if (key == 'A' && snakebody[0].ModX != 1) {
            snakebody[0].ModX = -1;
            snakebody[0].ModY = 0;
        }
        if (key == 'D' &&  snakebody[0].ModX != -1) {
            snakebody[0].ModX = 1;
            snakebody[0].ModY = 0;
        }
        if(key==ESC){
                        sys_beep(300,5);
                        print("The game has finished. You pressed ESC ");
                        sys_sleep(1000);
                        sys_clear_screen();
                        return -1;
                    }

    }
    return 1;
}

void update(char campo[V][H], int tam) {
    Intro_Field(campo);
    Intro_Data2(campo, tam);

    if (fruitEaten) {
        srand(getSeconds());
        do {
            fruit.x = rand() % (H - 2) + 1;
            fruit.y = rand() % (V - 2) + 1;
        } while (checkOverlap(fruit.x, fruit.y, snakebody, tam));
        fruitEaten = 0; // Restablish the flag
    }
}

void Intro_Data2(char campo[V][H], int tam) {
    // Creates body movements of the snake body
    for (int i = tam - 1; i > 0; i--) {
        snakebody[i].x = snakebody[i - 1].x;
        snakebody[i].y = snakebody[i - 1].y;
    }
    snakebody[0].x += snakebody[0].ModX;
    snakebody[0].y += snakebody[0].ModY;

    for (int i = 0; i < tam; i++) {
        campo[snakebody[i].y][snakebody[i].x] = snakebody[i].imagen;
    }

    campo[fruit.y][fruit.x] = 'a';
}

int wscreen;
int hgt = 500;
int wdth = 900;
int tp = 5;
int bttm;
int lft;
int r;

void snake() {
    char key;
    sys_clear_screen();
    sys_get_screen_width(&wscreen);

    bttm = tp + hgt;
    lft = (wscreen-wdth)/2;
    r = wscreen-(wscreen-wdth)/2;

    print("Press ENTER to play in the DEFAULT MODE (1 single player)");
    enter();
    print("Press ESC to leave the game at any moment");
    enter();
    print("Instructions to play snake are: ");
    enter();
    print("The snake should eat the fruit ball that will appear automatically on the screen.");
    print("To make the snake move,");
    enter();
    sys_write(" Press 'W' to go UP, press 'S' to go down, press 'D' to turn left, press 'A' to turn right",RED);
    enter();
    print("Choose 1 or 2 players by pressing 1 or 2, respectively.");
    enter();

    int tam;
    char campo[V][H];

    while(1){
        key=getKey();
        if(key==ESC){
            sys_clear_screen();
            return;
        }
        if (key == '1' || key == '\n') {
            sys_write("You have chosen 1 player mode.  Loading game....",RED);
            enter();
            sys_sleep(800);
            init(&tam,campo);
            loop(campo, tam);
            return;
        }
        if (key == '2') {
            sys_write("You have chosen 2 players mode. Loading game....",RED);
            enter();
            sys_sleep(800);

            //init(&tam1, &tam2, campo);
           // loop(campo, tam1, tam2);
            return;
        }

    }
}

