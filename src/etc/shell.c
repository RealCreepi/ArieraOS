#include "shell.h"

char* prompt = "$ ";
int prompt_color = 0xFFFFFF;

int terminal_row;
int terminal_column;

void print_c(char c, int fgcolor) {
    if (c == '\n') {
        terminal_row++;
        terminal_column = 0;
    } else {
        drawchar(c, (terminal_column), (terminal_row + 1), fgcolor, 0x000000);
        terminal_column++;
        if (terminal_column >= SCREEN_WIDTH) {
            terminal_column = 0;
            terminal_row++;
            if (terminal_row >= SCREEN_HEIGHT){
                terminal_row = 0;
                fillrect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0x000000);
            }
        }
    }
}

void print(char* str, int fgcolor) {
	for (size_t i = 0; i < strlen(str); i++) {
        print_c(str[i], fgcolor);
    }
}

char* input(int fgcolor){
    uint8_t key; int c = 0;

    while(key != 0x1C){
        while(!(key = keyboard_read_key())) {}
        if(key == 0xE && c > 0){
            inp[c--] = '\0';
            terminal_column--; drawchar(c, (terminal_column), (terminal_row + 1), 0x000000, 0x000000);
            continue;
        }
        if(key == 0x2A){
            while(key != 0xAA){
                while(!(key = keyboard_read_key())) {}
                if(key == 0xE && c > 0){
                    inp[c--] = '\0';
                    terminal_column--; drawchar(c, (terminal_column), (terminal_row + 1), 0x000000, 0x000000);
                    continue;
                }
                if(ktocSHIFT(key) != 0){
                    inp[c++] = ktocSHIFT(key);
                    print_c(ktocSHIFT(key), fgcolor);
                }
            }
        }
        if(ktoc(key) != 0) {
            inp[c++] = ktoc(key);
            print_c(ktoc(key), fgcolor);
        }
    }
    inp[c] = '\0';
    return inp;
}

bool reboot() {
    uint8_t good = 0x02;
    while (good & 0x02)
        good = inportb(0x64);
    outportb(0x64, 0xFE);
    asm("hlt");

    return true;
}

bool shutdown() {
    if(shutdownSupported()) {
        acpiPowerOff();
        return true;
    }
    return false;
}

bool sysinfo(multiboot_info_t* mbi, char* kernel_ver) {
    print("\nKernel: ", 0xFFFF00);
    print(kernel_ver, 0xFFFFFF);
    print("\nUptime: ", 0xFFFF00);
    print(itoa(get_timer_ticks()/1000,10), 0xFFFFFF);
    print("s", 0xFFFFFF);
    print("\nTotal memory: ", 0xFFFF00);
    print(itoa(mbi->mmap_addr / 1000,10), 0xFFFFFF);
    print(" MB", 0xFFFFFF);

    return true;
}

void commandHandler(multiboot_info_t* mbi, char* kernel_ver, char* cmd, int uid) {
    if(strequ(cmd, "")) {}
    else if(strequ(cmd, "reboot"))
        reboot();
    else if(strequ(cmd, "shutdown"))
        shutdown();
    else if(strequ(cmd, "sysinfo"))
        sysinfo(mbi, kernel_ver);
    else {
        print("\n", 0xFFFFFF);
        print(cmd, 0xFFFFFF);
        print(": command not found", 0xFFFFFF);
    }
}

void shell(multiboot_info_t* mbi, char* kernel_ver, int uid) {
    while(true){
        print("\n", 0xFFFFFF); 
        print(UIDs[uid], 0xFF0000); 
        print(prompt, prompt_color);
        
        char* cmd = input(0xFFFFFF);

        commandHandler(mbi, kernel_ver, cmd, uid);
    }
}