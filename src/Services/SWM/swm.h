#pragma once

void InitSWM_task();

typedef struct Window_struct Window;
Window* Window_new(unsigned int x, unsigned int y,
                   unsigned int width, unsigned int height);