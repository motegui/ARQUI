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
		if ((letter[0] >= '0' && letter[0]<= '9') || (letter[0] >= 'A' && letter[0]<= 'Z') && letter[0]!='\n'){
			sys_write(letter, WHITE);
			buffer[i++]=letter[0];
		}
        if(letter[0]=='\b' && i>0){
            sys_write(letter, WHITE);
            i-=1;
        }
	}
	buffer[i]='\0';
    enter();
}

void deleteInitialFinalSpace(char * string){
    int i=0;
    while(string[i]==' '){
        i++;
    }
    int j=0;
    if(i!=0){
        while(string[i-1]!='\0'){
            string[j]=string[i];
            i++;
            j++;
        }
    }

    int length;
    for(length=0; string[length]!='\0'; length++){}
    while(string[length-1]==' '){
        string[length-1]=string[length];
        length--;
    }
}
 
 void intToString(int number, char *str)
{
	if (number == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return;
	}
	int i = 0;
	while (number > 0)
	{
		int digit = number % 10;
		str[i++] = digit + '0';
		number /= 10;
	}
	str[i] = '\0';
	// Reverse the string
	int start = 0;
	int end = i - 1;
	while (start < end)
	{
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}



//reading
int getChar(){
    char c = 0;
    sys_read(&c);
    return c;
}


//printing
void print(char * string){
	sys_write(string, WHITE);

}

void printChar(char c){
    sys_write(&c ,WHITE);
}

void printLine(char * string){
    print(string);
    printChar('\n');
}

//strings
int strlen(char * string){
    int i = 0;
    while(string[i++] != 0);
    return i-1;
}

void printBase(uint64_t value, uint32_t base){
    char buf[20];
    uintToBase(value, buf, base);
    print(buf);
}

void printHexa(uint64_t value){
    char buf[20];
    int digits = uintToBase(value, buf, 16);
    fillHexa(16-digits, buf);
    print(buf);
}

//la sacamos de naiveConsole
uint32_t uintToBase(uint64_t value, char * buffer, uint32_t base){
    char *p = buffer;
    char *p1, *p2;
    uint32_t digits = 0;

    //Calculate characters for each digit
    do{
        uint32_t remainder = value % base;
        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
        digits++;
    }
    while (value /= base);

    // Terminate string in buffer.
    *p = 0;

    //Reverse string in buffer.
    p1 = buffer;
    p2 = p - 1;
    while (p1 < p2)
    {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }

    return digits;
}

void fillHexa(int num, char* buf){ //para llenar los 0 de los hexa
    for(int i = 15; i >= 0; i--){
        if(i >= num){
            buf[i] = buf[i-num];
        }else{
            buf[i] = '0';
        }
    }
    buf[16] = '\0';
}
