#include <keyboard_driver.h>
#include <video.h>
#include <lib.h>
#include <naiveConsole.h>
#include <stdbool.h>
#define BUFF_SIZE 256
#define TECLA_LIMITE_SUPERIOR 90
#define CONTROL 0x1D

static char buff[BUFF_SIZE] = {0}; // este va a ser mi vector circular(cuando el buff alcanza su max capacidad, los nuevos elementos sobreescriben los que estan en las posiciones mas antiguas), y este lo usamos como un buffer de teclado
static int front = 0;              // indica la posicion del primer elemento
static int rear = 0;               // indica la posicion del ultimo elemento agregado
static int cantElems = 0;
bool savedRegs = false; 

char nextElement()// este va a ser mi vector circular(cuando el buff alcanza su max capacidad, los nuevos elementos sobreescriben los que estan en las posiciones mas antiguas), y este lo usamos como un buffer de teclado

{

    if (cantElems == 0) {
        return -1;
    }

    char c = buff[front];

    cantElems--;
    front++;

    if (front == BUFF_SIZE) front = 0;

    return c;

}

int cantElements(){
    return cantElems;
}

void cleanBuffer(){
    cantElems=0;
    front=0;
    rear=0;
}

void keyHandler(uint64_t scancode)
{
    char tecla = scancode;

    if (tecla <= TECLA_LIMITE_SUPERIOR)
    {
        if (cantElems == BUFF_SIZE)
        {
            return;
        }
       if(tecla == CONTROL){
            savedRegs = true;
            return;
        }
    
       // los dos if de abajo son necesarios para mantener el funcionamiento circular del buffer
        if (rear == BUFF_SIZE)
            rear = 0;
        if (front == BUFF_SIZE)
            front = 0;
        buff[rear++] = keyBoardTable[tecla];
        cantElems++;
    }

}

bool isRegsSaved(){
    return savedRegs;
}
