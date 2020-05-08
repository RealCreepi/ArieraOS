#pragma once
#include <stdint.h>
#include "../common.h"

#define MOUSE_WIDTH 5
#define MOUSE_HEIGHT 5

uint8_t mouseCycle;
uint8_t mouseByte[3];
int16_t mouseX;
int16_t mouseY;

uint8_t mouse_read();
void handleMouseDown(uint8_t key);
void handleMouseUp(uint8_t key);