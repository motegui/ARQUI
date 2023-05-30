#include <keyboard_driver.h>
#include <video.h>
#include <lib.h>
#include <naiveConsole.h>
#define BUFF_SIZE 256
#define TECLA_LIMITE_SUPERIOR 90
#define ENTER 0x1C
#define CONTROL 0x1D

extern uint64_t * registers;
extern uint64_t * getRegs();

static char buff[BUFF_SIZE] = {0}; // este va a ser mi vector circular(cuando el buff alcanza su max capacidad, los nuevos elementos sobreescriben los que estan en las posiciones mas antiguas), y este lo usamos como un buffer de teclado
static int front = 0;              // indica la posicion del primer elemento
static int rear = 0;               // indica la posicion del ultimo elemento agregado
static int cantElems = 0;
extern char kbFlag();

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

void keyHandler()
{
    char tecla = kbFlag();

    if (tecla <= TECLA_LIMITE_SUPERIOR)
    {
        if (cantElems == BUFF_SIZE)
        {
            return;
        }
       if(tecla == CONTROL){
            registers = getRegs();
            putArrayNext("Saving registers",GREEN);
        }
       // los dos if de abajo son necesarios para mantener el funcionamiento circular del buffer
        if (rear == BUFF_SIZE)
            rear = 0;
        if (front == BUFF_SIZE)
            front = 0;
        buff[rear++] = keyBoardTable[tecla];
        cantElems++;
    }
    

        // if(tecla >= 0x01 && tecla <=0x3A) {
        //     switch (tecla)
        //     {
        //     case ENTER:
        //         putLine();
        //         cantElems--;
        //         return;
        //     default:
        //         break;
        //     }
        // }

        // if (tecla >= 0 && tecla <= 90 && keyBoardTable[tecla] != 0)
        // {
        //     //putLetterNext(keyBoardTable[tecla], WHITE);
        //     cantElems--;
        //     return;
        // }

}
