#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

uint8_t* screen;

void putpixel(int x,int y, int color);
void fillrect(int px, int py, int sx, int sy, int color);
inline uint8_t vga_entry_color(uint8_t fg, uint8_t bg);
inline uint16_t vga_entry(unsigned char uc, uint8_t color);
void drawchar(unsigned char c, int x, int y, int fgcolor, int bgcolor);
void drawstring(unsigned char* c, int x, int y, int fgcolor, int bgcolor);