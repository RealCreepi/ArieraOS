#include "../all_drivers.h"
#include "../common.h"

void keyboard_send_key(uint8_t b){
    outportb(0x64, b);
}

uint8_t keyboard_read_key()
{
    uint8_t key_code = 0;
	if (inportb(0x64) & 1){
        key_code = inportb(0x60);
        
        while(key_code==0){}
        return key_code;
	}
    return 0;
}