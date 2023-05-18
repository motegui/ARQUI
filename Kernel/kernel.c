#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <video.h>
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define YELLOW 0xFFFF00
#define  ORANGE 0xFFA500
void draw_string(int x, int y, char* input, int len, int color, int backgroundColor);
void draw_char(int x, int y, char letter, int color, int backgroundColor);
void set_default_fontSize(int size);
int get_default_fontSize();
void fillrect(int x, int y, int color, int w, int h);
int DEFAULT_LETTER_SIZE = 8; // Tamaño de letra predeterminado

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};
	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);
	return getStackBase();
}
//uint8_t r = 0;
//uint8_t g = 0;
//uint8_t b = 255;
int main()
{
	ncPrint("[Kernel Main]");
	// printPixelsInFullScreen(r, g, b);
	 set_default_fontSize(16); // Establece el tamaño de letra predeterminado a 16

    char text[] = "Hello, World!";
    int x = 100;
    int y = 100;
    int color = 0xFF0000; // Rojo
    int backgroundColor = 0x000000; // Negro

    draw_string(x, y, text, sizeof(text) - 1, color, backgroundColor);
	return 0;
}
