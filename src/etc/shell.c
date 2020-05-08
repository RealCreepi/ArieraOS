#include "shell.h"

char* prompt = "$ ";
int prompt_color = VGA_COLOR_WHITE;

void shell(multiboot_info_t* mbi, unsigned int magic, char* kernel_ver, char* kernel_type) {
    while(true){
        print("\n"); print_c(prompt, prompt_color);
        char buf[128]; char* cmd = inputs(buf);

        if(strequ(cmd, "mouse")) {
            print("\nmouseX:");
            print(itoa(mouseX, 10));
            print("\nmouseY:");
            print(itoa(mouseY, 10));
        } else
        if(strequ(cmd, "reboot")){
            uint8_t good = 0x02;
            while (good & 0x02)
                good = inportb(0x64);
            outportb(0x64, 0xFE);
            asm("hlt");   
        } else
        if(strequ(cmd, "shutdown")){
            acpiPowerOff();
        } else
        if(strequ(cmd, "sysinfo")){
            print_c("\nKernel: ", VGA_COLOR_BLUE);
            print(kernel_ver);
            print(kernel_type);
            print_c("\nUptime: ", VGA_COLOR_BLUE);
            print(itoa(get_timer_ticks()/1000,10));
            print("s");
            print_c("\nTotal memory: ", VGA_COLOR_BLUE);
            print(itoa(mbi->mmap_addr / 1000,10));
            print(" MB\n");
            print_c("Time and date: ", VGA_COLOR_BLUE);
            rtc_print_formatted_time();
        }else
        if(strequ(cmd, "timectl")){
            print("\n");
            rtc_print_formatted_time();
        }else if(strequ(cmd, "")) {
        }else
        {
            print("\n");
            print(cmd);
            print(": command not found");
        }
    }
}