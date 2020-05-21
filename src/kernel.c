#include "common.h"
#include "all_drivers.h"
#include "all_etc.h"

char* kernel_ver = "ArieraOS-1.0-alpha";
bool GMode = true; // false = graphics mode disabled; true = graphics mode enabled

unsigned int terminal_start;

void kernel_main(multiboot_info_t* mbi, unsigned int magic)
{
    screen = (void*)mbi->framebuffer_addr;
    //fillrect(0, 0, VGA_WIDTH, VGA_HEIGHT, 0xFFFFFF);

    gdt_install();
    idt_install();
    irq_install();
    __asm__ __volatile__ ("sti");

    isrs_install();
    timer_install(1000);
    mouse_install(); // only used to stop OS from hanging at mouse input
    initAcpi();
    
    bootbeep();
    //InitSWM_task();
    shell(mbi, kernel_ver, 0);
}
