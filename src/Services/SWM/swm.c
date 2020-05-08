#include "../../all_drivers.h"
#include "../../common.h"

//WINDOW//

typedef struct Window_struct {
    int x;
    int y;
    int width;
    int height;
} Window;

Window* Window_new(int x, int y, int width, int height) {
    Window* window;

    window->x = x;
    window->y = y;
    window->width = width;
    window->height = height;

    return window;
}

void Window_paint(Window* window) {
    fillrect(window->x, window->y, window->width, window->height, 0xAEB1B7);
}

//MAIN//

void PaintDesktop(){
    fillrect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xADD8E6);
    //Window_paint(Window_new(10, 10, 300, 200));
}

void PaintCursor(){
    //just make a white box at the cursor position:
    fillrect(mouseX, mouseY, MOUSE_WIDTH, MOUSE_HEIGHT, 0x000000);
}

void ScreenRefreshProc(){
    PaintDesktop(); //paints the desktop and all windows
    PaintCursor(); //finally paints the cursor so it's on top
/*#if WAIT_FOR_VERTICAL_RETRACE
        while ((inportb(0x3DA) & 0x08));
        while (!(inportb(0x3DA) & 0x08));
#endif*/
}