#include <video.h>
VBEInfoPtr VBE_mode_info = (VBEInfoPtr)0x0000000000005C00;

// void putPixel(uint32_t hexColor, uint32_t x, uint32_t y) {
// 	uint8_t * screen = (uint8_t *) ((uint64_t) (VBE_mode_info->framebuffer));
//     uint32_t offset = VBE_mode_info->pitch*y + x*3;

//     screen[offset] = hexColor & 0xFF;
//     screen[offset+1] = (hexColor >> 8) & 0xFF;
//     screen[offset+2] = (hexColor >> 16) &  0xFF;
// }

void putPixel(uint8_t r, uint8_t g, uint8_t b, uint32_t x, uint32_t y)
{
	uint8_t *videoPtr = VBE_mode_info->framebuffer;
	int offset = y * VBE_mode_info->pitch + x * (VBE_mode_info->bpp / 8);
	videoPtr[offset] = b;
	videoPtr[offset + 1] = g;
	videoPtr[offset + 2] = r;
}
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
