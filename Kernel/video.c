
#include <video.h>
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16
static int pointer_x = 0;
static int pointer_y = 0;
struct vbe_mode_info_structure
{
	uint16_t attributes;  // deprecated, only bit 7 should be of interest to you, and it indicates the mode supports a linear frame buffer.
	uint8_t window_a;	  // deprecated
	uint8_t window_b;	  // deprecated
	uint16_t granularity; // deprecated; used while calculating bank numbers
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr; // deprecated; used to switch banks from protected mode without returning to real mode
	uint16_t pitch;		   // number of bytes per horizontal line
	uint16_t width;		   // width in pixels
	uint16_t height;	   // height in pixels
	uint8_t w_char;		   // unused...
	uint8_t y_char;		   // ...
	uint8_t planes;
	uint8_t bpp;   // bits per pixel in this mode
	uint8_t banks; // deprecated; total number of banks in this mode
	uint8_t memory_model;
	uint8_t bank_size; // deprecated; size of a bank, almost always 64 KB but may be 16 KB...
	uint8_t image_pages;
	uint8_t reserved0;
	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;
	uint32_t framebuffer; // physical address of the linear frame buffer; write here to draw to the screen
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size; // size of memory in the framebuffer but not being displayed on the screen
	uint8_t reserved1[206];
} __attribute__((packed));
typedef struct vbe_mode_info_structure *VBEInfoPtr;
VBEInfoPtr VBE_mode_info = (VBEInfoPtr)0x0000000000005C00;

void putPixel(uint32_t hexColor, uint32_t x, uint32_t y)
{
	uint8_t *screen = (uint8_t *)((uint64_t)(VBE_mode_info->framebuffer));
	uint32_t offset = VBE_mode_info->pitch * y + x * 3;
	screen[offset] = hexColor & 0xFF;
	screen[offset + 1] = (hexColor >> 8) & 0xFF;
	screen[offset + 2] = (hexColor >> 16) & 0xFF;
}
void putLetter(int caracter, uint32_t x, uint32_t y, int color)
{
	unsigned char *bitMap = charBitmap(caracter);
	for (int j = 0; j < CHAR_HEIGHT; j++)
	{
		for (int i = 0; i < CHAR_WIDTH; i++)
		{
			uint8_t bit = ((bitMap[j]) >> i) & 0x01;
			if (bit == 1)
			{
				// Llamar a putPixel cuando el bit es 1
				putPixel(color, x + 7 - i, j + y); // Ejemplo: Establecer el píxel en rojo en la fila 0
			}
		}
	}
}
void putArray(char *array, uint32_t x, uint32_t y, int color)
{
	int i = 0;
	int aux_y = y;
	int aux_x = x;
	while (array[i] != '\0')
	{
		if (aux_x + CHAR_HEIGHT > VBE_mode_info->width)
		{
			aux_x = 0;
			aux_y = aux_y + CHAR_HEIGHT + 1;
		}
		putLetter(array[i], aux_x, aux_y, color);
		i++;
		aux_x = aux_x + CHAR_WIDTH + 1;
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
void putDec(int number, uint32_t x, uint32_t y, int color)
{
	char *strNumber;
	intToString(number, strNumber);
	putArray(strNumber, x, y, color);
}
void putLetterNext(int caracter, int color)
{
	if (pointer_x + CHAR_HEIGHT > VBE_mode_info->width)
	{
		pointer_x = 0;
		pointer_y = pointer_y + CHAR_HEIGHT + 1;
	}
	unsigned char *bitMap = charBitmap(caracter);
	for (int j = 0; j < CHAR_HEIGHT; j++)
	{
		for (int i = 0; i < CHAR_WIDTH; i++)
		{
			uint8_t bit = ((bitMap[j]) >> i) & 0x01;
			if (bit == 1)
			{
				// Llamar a putPixel cuando el bit es 1
				putPixel(color, pointer_x + 7 - i, j + pointer_y); // Ejemplo: Establecer el píxel en rojo en la fila 0
			}
		}
	}
	pointer_x = pointer_x + CHAR_WIDTH + 1;
}
void putArrayNext(char *array, int color)
{
	int i = 0;
	while (array[i] != '\0')
	{
		putLetterNext(array[i], color);
		i++;
	}
}
void putDecNext(int number, int color)
{
	char *strNumber;
	intToString(number, strNumber);
	putArrayNext(strNumber, color);
}
void putLine()
{
	pointer_y = pointer_y + CHAR_HEIGHT + 1;
	pointer_x = 0;
}

//  void deleteChar(){
// 	if(pointer_x==0){
// 		pointer_x = pointer_x - CHAR_HEIGHT;
//  	}
//  }
