#include "common.h"
#include "all_drivers.h"

#if !defined(__i386__)
#error "This needs to be compiled with i686"
#endif


void kernel_main(void)
{
    gdt_install();
    idt_install();
    isrs_install();
    irq_install();
    __asm__ __volatile__ ("sti");
    terminal_initialize();
    timer_install();

	terminal_initialize();
	terminal_writestr_c("                ooooo      ssss\n", 0xC);
    terminal_writestr_c("              oo     oo   ss   \n", 0x7);
    terminal_writestr_c("mm  mm  mm    oo     oo    sss \n", 0x9);
    terminal_writestr_c("mmmm  mm  mm  oo     oo      ss\n", 0xD);
    terminal_writestr_c("mm    mm  mm  oo     oo     ss \n", 0xC);
    terminal_writestr_c("mm    mm  mm  oo     oo  ssss  \n", 0x7);
    terminal_writestr_c("mm    mm  mm    ooooo          \n\n", 0xF);
    terminal_writestr("Welcome! Wilkommen! Bun venit! Dobro dosli!\n");
    sleep(1000);
    char* cmd;
    while(true){
        terminal_writestr("mountainOS> ");
        cmd = input();
        terminal_writestr("\n");
        if(strequ(cmd, "hi")){
            terminal_writestr("Hi!\n");
        }
        if(strequ(cmd, "hello")){
            terminal_writestr("Hi!\n");
        }
        if(strequ(cmd, "crash")){
            itoa(32 / 0, 10);
        }
    }

}
