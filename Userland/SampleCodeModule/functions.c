#include <stdint.h>
#include <functions.h>
#include <user_syscalls.h>


//https://www.techiedelight.com/es/implement-strcmp-function-c/
// Función para implementar la función strcmp
int strcmp(char *X, char *Y)
{
    while (*X)
    {
        // si los caracteres difieren o se llega al final de la segunda string
        if (*X != *Y) {
            break;
        }
 
        // pasar al siguiente par de caracteres
        X++;
        Y++;
    }
 
    // devuelve la diferencia ASCII después de convertir `char*` a `unsigned char*`
    return *(const unsigned char*)X - *(const unsigned char*)Y;
}

void scanf(char * buffer, int bufferSize){
    char letter[2];
	letter[1]='\0';
    int i=0;
	while(letter[0] != '\n' && i<bufferSize-1){
		sys_read(letter);
		if (letter[0] != -1 && letter[0]!= 0 && letter[0]!='\n'){
			sys_write(letter, WHITE);
			buffer[i++]=letter[0];
		}
        if(letter[0]=='\b'){
            i-=2;
        }
	}
	buffer[i]='\0';
    enter();
}
 