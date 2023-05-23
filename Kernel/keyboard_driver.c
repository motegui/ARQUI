#include <keyboard_driver.h>
#include <video.h>
#include <lib.h>
#include <naiveConsole.h>
#define BUFF_SIZE 256
#define TECLA_LIMITE_SUPERIOR 0X79
static char buff[BUFF_SIZE] = {0}; // este va a ser mi vector circular(cuando el buff alcanza su max capacidad, los nuevos elementos sobreescriben los que estan en las posiciones mas antiguas), y este lo usamos como un buffer de teclado
static int front = 0;              // indica la posicion del primer elemento
static int rear = 0;               // indica la posicion del ultimo elemento agregado
static int cantElems = 0;
extern char kbFlag();

char nextElement()
{ // se usa para obtener el sig elto en el buffer circular
    if (cantElems <= 0)
    {
        return -1;
    }
    char toReturn = buff[front];
    front = (front + 1) % BUFF_SIZE; // esto es para chequear que no se vaya del tamaño definido para BUFF_SIZE
    cantElems--;
    return toReturn;
}

void keyHandler()
{
    unsigned char tecla = kbFlag();
    // esta funcion se llama cada vez que alguien presiona una tecla, lo del limte superior es para
    // evitar que se incluya tmb un press de liberacion de la tecla debido a que tienen codigos diferentes

    if (tecla <= TECLA_LIMITE_SUPERIOR)
    {
        if (cantElems == BUFF_SIZE)
        {
            return;
        }
        // los dos if de abajo son necesarios para mantener el funcionamiento circular del buffer
        if (rear == BUFF_SIZE)
            rear = 0;
        if (front == BUFF_SIZE)
            front = 0;
        buff[rear++] = keyBoardTable[tecla];
        putLetterNext(keyBoardTable[tecla], WHITE);
        cantElems++;
    }
}
