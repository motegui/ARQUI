/* sampleCodeModule.c */
#include <stdint.h>
#include <time_driver.h>
#include <user_syscalls.h>


#define BLACK 0x000000
#define GREEN 0x00FF00
#define RED 0xFF0000
#define WHITE 0xFFFFFF
#define CORAL 0xFF7F50
#define PINK 0xFF69B4

char * v = (char*)0xB8000 + 79 * 2;


// static int var1 = 0;
// static int var2 = 0;


int main() {
	// //All the following code may be removed 
	// *v = 'X';
	// *(v+1) = 0x74;

	// //Test if BSS is properly set up
	// if (var1 == 0 && var2 == 0)
	// 	return 0xDEADC0DE;

	// return 0xDEADBEEF;
	getTime(WHITE);

	enter();
	
	sys_write("hola", WHITE);

	char  letter[2];
	letter[1]='\0';

	while(1){
		sys_read(letter);
		if (letter[0] != -1 && letter[0]!= 0){
			sys_write(letter, WHITE);
		}
	}

	return 0;
}