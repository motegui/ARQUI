#include <video.h>
#include <lib.h>
#include <font.h>
VBEInfoPtr VBE_mode_info = (VBEInfoPtr)0x0000000000005C00;
#define SCREEN_W screenInformation->width
#define SCREEN_H screenInformation->height
struct vbe_mode_info_structure *screenInformation = (void *)0x5C00; // Information loaded in function sysvar in Bootloader
static int DEFAULT_LETTER_SIZE = 1;
unsigned char getRed(int color)
{
	return (color >> 16) & 255;
}

unsigned char getBlue(int color)
{
	return color & 255;
}

unsigned char getGreen(int color)
{
	return (color >> 8) & 255;
}

int getPosition(int x, int y)
{
	return x * (screenInformation->bpp) / 8 + y * (screenInformation->pitch);
}

int getXPos(int x)
{
	if (x < SCREEN_W)
	{
		return x;
	}
	return SCREEN_W;
}

int getYPos(int y)
{
	if (y < SCREEN_H)
	{
		return y;
	}
	return SCREEN_H;
}

void putPixel(uint32_t hexColor, uint32_t x, uint32_t y)
{
	uint8_t *screen = (uint8_t *)((uint64_t)(VBE_mode_info->framebuffer));
	uint32_t offset = VBE_mode_info->pitch * y + x * 3;

	screen[offset] = hexColor & 0xFF;
	screen[offset + 1] = (hexColor >> 8) & 0xFF;
	screen[offset + 2] = (hexColor >> 16) & 0xFF;
}

// esta es una funcion para imprimir pixeles en toda la pantalla
// void printPixelsInFullScreen(uint8_t r, uint8_t g, uint8_t b) {
//   // Get the framebuffer address.
//   uint8_t *videoPtr = VBE_mode_info->framebuffer;

//   // Loop over all pixels in the screen.
//   for (int x = 0; x < VBE_mode_info->width; x++) {
//     for (int y = 0; y < VBE_mode_info->height; y++) {
//       // Set the pixel at (x, y) to the specified color.
//       putPixel(r, g, b, x, y);
//     }
//   }
// }

void fillrect(int x, int y, int color, int w, int h)
{

	if (x > SCREEN_W || y > SCREEN_H)
		return;
	int i, j;
	if (w + x > SCREEN_W)
		w = SCREEN_W - x;
	if (h + y > SCREEN_H)
		h = SCREEN_H - y;

	uint8_t *aux = (uint8_t *)((uint64_t)screenInformation->framebuffer + getPosition(x, y));
	int blue = getBlue(color);
	int red = getRed(color);
	int green = getGreen(color);

	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			aux = (uint8_t *)((uint64_t)screenInformation->framebuffer + getPosition(x + i, y + j));
			*(aux) = blue;		// BLUE
			*(aux + 1) = green; // GREEN
			*(aux + 2) = red;	// RED
		}
	}
}

void clearScreen()
{
	fillrect(0, 0, BLACK, SCREEN_W, SCREEN_H);
}
/*
primero se chequea que los caracteres se ajusten precisamente a los limites de la pantalla.
Comparo la pos actual (xInter) mas el ancho de su caracter (letterWidth) con el ancho de la pantalla
menos el ancho de un caracter (SCREEN_W - letterWidth). Con esto me aseguro de que voy a seguir
teniendo espacio para otra letra en la misma linea .
Si la pos excede este limite, aumento la pos vertical yInter y reinicio xInter(la horizontal)
*/

void draw_string(int x, int y, char *input, int len, int color, int backgroundColor)
{
	int xInter = x;
	int yInter = y;

	for (int i = 0; i < len; i++)
	{
		char letter = input[i];
		int letterWidth = DEFAULT_LETTER_SIZE * CHAR_WIDTH;

		// Verifica si la posición actual excede el ancho de la pantalla menos el ancho de un carácter
		if (xInter + letterWidth > SCREEN_W - letterWidth)
		{
			// Si excede, pasa a la siguiente línea
			yInter += CHAR_HEIGHT * DEFAULT_LETTER_SIZE;
			xInter = x;
		}

		draw_char(xInter, yInter, letter, color, backgroundColor);
		xInter += letterWidth;
	}
}

/*En draw_char se utiliza una máscara de bits (bitMask) para comprobar cada bit individual en la fila del
bitmap. Se realiza una operación AND entre la máscara de bits y la fila del bitmap (bitmapRow & bitMask)
 para determinar si el bit está presente o no. luego con esta data vemos q color le ponemos al relleno
*/
// void draw_char(int x, int y, char letter, int color, int backgroundColor) {
//     int aux_x = x;
//     int aux_y = y;

//     unsigned char* toDraw = charBitmap(letter);

//     for (int i = 0; i < CHAR_HEIGHT; i++) {
//         unsigned char bitmapRow = *(toDraw + i);

//         for (int j = 0; j < CHAR_WIDTH; j++) {
//             unsigned char bitMask = 0x80 >> j;  // Máscara de bits para el bit actual

//             // Comprueba si el bit está presente en la fila del bitmap
//             if (bitmapRow & bitMask)
//                 fillrect(aux_x, aux_y, color, DEFAULT_LETTER_SIZE, DEFAULT_LETTER_SIZE);
//             else
//                 fillrect(aux_x, aux_y, backgroundColor, DEFAULT_LETTER_SIZE, DEFAULT_LETTER_SIZE);

//             aux_x += DEFAULT_LETTER_SIZE;
//         }

//         aux_x = x;
//         aux_y += DEFAULT_LETTER_SIZE;
//     }
// }

// void set_default_fontSize(int size) {
//     DEFAULT_LETTER_SIZE = size;
// }

// int get_default_fontSize() {
//     return DEFAULT_LETTER_SIZE;
// }

// void putChar(int x, int y, char caracter, int color, int backgroundColor)
// {
//     unsigned char *bitMap = charBitmap(caracter);
//     for (int j = 0; j < CHAR_HEIGHT; j++)
//     {
//         for (int i = 0; i < CHAR_WIDTH; i++)
//         {
//             uint8_t bit = ((bitMap[j]) >> i) & 0x01;
//             if (bit == 1)
//             {
//                 // Llamar a putPixel cuando el bit es 1
//                 putPixel(color, x + 7 - i, j + y); // Ejemplo: Establecer el píxel en rojo en la fila 0
//             }
// 			else{
// 				putPixel(backgroundColor, x + 7 - i, j + y);
// 			}
//         }
//     }
// }
// void putArray(char *array, uint32_t x, uint32_t y,  int color, int backgroundColor){
//     int length = sizeof(array) / sizeof(array[0]);
//     int i = 0;
// 	int aux_x=x;
//     while (i < length)
//     {
// 		if(aux_x+CHAR_WIDTH>SCREEN_W){}
//         putChar(array[i], aux_x, y, color, backgroundColor);
//         i++;
//     }
// }
