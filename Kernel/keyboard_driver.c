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
    int tecla = kbFlag();
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
        cantElems++;
    }
      if (tecla == 0x39) // Tecla de espacio
    {
        ncPrint(" ");
        return;
    }
    if (keyBoardTable[tecla] == '\b') // Retroceso
    {
        ncBackspace();
        return;
    }
    if (keyBoardTable[tecla] == '\t') // Tabulación
    {
        ncPrint("    ");
        return;
    }
    if (keyBoardTable[tecla] == '\n') // Nueva línea
    {
        ncNewline();
        return;
    }
    if (tecla >= 0 && tecla <= 256 && keyBoardTable[tecla] != 0)
    {
        putLetterNext(keyBoardTable[tecla], WHITE);
        return;
    }
}
