#include "../../all_drivers.h"
#include "../../common.h"

//WINDOW//

typedef struct Window_struct {
    int x;
    int y;
    int lastX;
    int lastY;

    int width;
    int height;
    int lastWidth;
    int lastHeight;

    int color;
    
    bool update;
} Window;

/*Window* Windows[64];

void Windows_add(Window* window) {
    for(int i; i<64; i++) {
        if (!Windows[i]) {
            Windows[i] = window;
            break;
        }
    }
}

Window WindowNew(int x, int y, int width, int height, int color) {
    Window window = {
        x, y, 0, 0,
        width, height, 0, 0,
        color,
        true
    };

    return window;
}*/

void WindowUpdate(Window* window) {
    if (window->update){
        fillrect(window->lastX, window->lastY, window->lastWidth, window->lastHeight, 0xADD8E6);
        fillrect(window->x, window->y, window->width, window->height, window->color);
        window->update = false;
    }
}

//MAIN//

Window mouse = {
    0, 0, 0, 0,
    MOUSE_WIDTH, MOUSE_HEIGHT, MOUSE_WIDTH, MOUSE_HEIGHT,
    0xffffff,
    true,
};

Window panel = {
    0, 0, 0, 0,
    SCREEN_WIDTH, 30, SCREEN_WIDTH, 30,
    0x2A2F3A,
    true
};

void PaintDesktop(){
    /*for(int i; i<64; i++) {
        if(!(Windows[i] == NULL)) {
            Window* window = Windows[i];
            WindowUpdate(&window);
        }
    }*/

    WindowUpdate(&panel);
    WindowUpdate(&mouse);
}

void PaintCursor(){
    //just make a white box at the cursor position:
    if ((mouse.x != mouseX) || (mouse.y != mouseY)) {
        mouse.lastX = mouse.x; mouse.lastY = mouse.y;
        mouse.x = mouseX; mouse.y = mouseY;
        mouse.update = true;
    }
}

void ScreenRefreshProc(){
    PaintDesktop();
    PaintCursor();
}

void InitSWM() {
    fillrect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xADD8E6);
    
    /*Window panel = WindowNew(0, 0, SCREEN_WIDTH, 30, 0x2A2F3A);
    Windows_add(&panel);*/

    task_add(&ScreenRefreshProc, 10);
}