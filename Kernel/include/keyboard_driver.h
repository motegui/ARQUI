#include <stdbool.h>
#include <stdint.h>

char nextElement();
void keyHandler(uint64_t scancode);
int cantElements();
bool isRegsSaved();
void cleanBuffer();

static const char keyBoardTable[256] =
    {
          0,27,'1',  '2',  '3',  '4',  '5',  '6',   '7',  '8',
          '9',   '0',   '-',  '=','\b',' ','Q',  'W',  'E',  'R',
          'T',  'Y',  'U',  'I',   'O',  'P',  '[',   ']',  '\n',    0,
         'A', 'S','D','F',  'G',  'H',  'J',  'K',  'L',  ';',
          '\'', 0, 0,  '\\', 'Z', 'X', 'C','V','B','N',
          'M', ',', '.',  '/',  0,  '*',     0,  ' ',    0,     0,
           0,  0, 0,0,0,0,0,0,0,0,
            0,0,4,0,0,2,0,3,0,0,
            5,0,0,0,0,0 ,0,0,0,0
            // 2: left arrow
            // 3: right arrow
            // 4: up arrow
            // 5: down arrow 
};
