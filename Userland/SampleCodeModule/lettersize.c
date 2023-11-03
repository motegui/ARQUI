#include <functions.h>

void lettersize() {
    print("CHOOSE YOUR FONT SIZE (WE RECOMMEND A NUMBER LOWER OR EQUAL TO 3)\n");
    char buff[50];
    int buffPos = 0;
    char c;

    while(1){

        c = getChar();
        if (c!=-1 && c!=0){
            hold(1);
            if(c == '\n'){
                enter();
                buff[buffPos] = 0;
                setCharSize(myAtoi(buff));
                print("SIZE WAS CHANGED");
                enter();
                return;
            } else {
                if(!isDigit(c)){
                    print("DIGITS ONLY :( ABORTING...\n");
                    return;
                }
                buff[buffPos++] = c;
                printChar(c, WHITE);

            }
        }
    }
}
