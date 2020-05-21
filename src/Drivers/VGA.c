#include "../all_drivers.h"
#include "font.h"

uint8_t* screen = (uint8_t*)0xA0000;

void putpixel(int x,int y, int color) {
    unsigned where = x*3 + y*2400;
    screen[where] = color & 255;              // BLUE
    screen[where + 1] = (color >> 8) & 255;   // GREEN
    screen[where + 2] = (color >> 16) & 255;  // RED
}

void fillrect(int px, int py, int sx, int sy, int color) {
    for (int i = 0; i < sy; i++) {
        for (int j = 0; j < sx; j++) {
            putpixel(j+px, i+py, color);
        }
    }
}

inline uint8_t vga_entry_color(uint8_t fg, uint8_t bg)
{
	return fg | bg << 4;
}

inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t)uc | (uint16_t)color << 8;
}

void drawchar(unsigned char c, int x, int y, int fgcolor, int bgcolor)
{
	int cx,cy;
	int mask[8]={1,2,4,8,16,32,64,128};
	unsigned char *glyph=g_8x8_font+(int)c*8;
	
	x *= 8; y *= 8;

	for(cy=0;cy<8;cy++){
		for(cx=0;cx<8;cx++){
			putpixel(x+cx, y+cy-4, glyph[cy] & mask[8-1-cx] ? fgcolor : bgcolor);
		}
	}
}

void drawstring(unsigned char* c, int x, int y, int fgcolor, int bgcolor) {
	for(int i; i<strlen(c); i++) {
		drawchar(c[i], x + (i*8), y, fgcolor, bgcolor);	
	}
}