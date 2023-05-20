#include <stdint.h>
#define BLACK 0x000000
#define GREEN 0x00FF00
#define RED 0xFF0000
#define WHITE 0xFFFFFF
#define CORAL 0xFF7F50
#define PINK 0xFF69B4
#define INITIAL_FONT_SIZE 1

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16

void putLetter(int caracter, uint32_t x, uint32_t y, int color);
void putPixel(uint32_t hexColor, uint32_t x, uint32_t y);
void putArray(char *array, uint32_t x, uint32_t y, int color);
