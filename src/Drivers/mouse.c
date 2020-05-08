#include "../all_drivers.h"
#include "mouse.h"

uint8_t mouseCycle = 0;
uint8_t mouseByte[3];
int16_t mouseX = 256;
int16_t mouseY = 256;

void handleMouseDown(uint8_t key) {return;};
void handleMouseUp(uint8_t key) {return;};

void handleMouse() {
	switch(mouseCycle) {
	case 0: {
		mouseByte[0] = mouse_read();
		if((mouseByte[0] & 0x08) != 0) {
			mouseCycle++; // Only accept this as the first byte if the "must be 1" bit is set
		}
		//mouseCycle++;
		break;
	};
	case 1: {
		mouseByte[1] = mouse_read();
		mouseCycle++;
		break;
	};
	case 2: {
		mouseByte[2] = mouse_read();
		int8_t mouseXd = mouseByte[1];
		int8_t mouseYd = mouseByte[2];
		mouseCycle = 0;
		mouseX += mouseXd;
		mouseY -= mouseYd;

		if ((getBit(mouseByte[0], 0) != 0) || (getBit(mouseByte[0], 1) != 0))
      handleMouseDown(0);
		else
			handleMouseUp(0);
    
    if (mouseX > SCREEN_WIDTH)
      mouseX = SCREEN_WIDTH - MOUSE_WIDTH;
    else if (mouseX < 1)
      mouseX = 1 + MOUSE_WIDTH;

    if (mouseY > SCREEN_HEIGHT)
      mouseY = SCREEN_HEIGHT - MOUSE_HEIGHT;
    else if (mouseY < 1)
      mouseY = 1 + MOUSE_HEIGHT;

		break;
	  };
	}
}

uint8_t mouse_read()
{
  mouse_wait(0);
  return inportb(0x60);
}

inline void mouse_wait(uint8_t a_type)
{
  uint32_t _time_out=100000;
  if(a_type==0)
  {
    while(_time_out--)
    {
      if((inportb(0x64) & 1))
      {
        return;
      }
    }
    return;
  }
  else
  {
    while(_time_out--)
    {
      if((inportb(0x64) & 2)==0)
      {
        return;
      }
    }
    return;
  }
}

inline void mouse_write(uint8_t a_write){
  mouse_wait(1);
  outportb(0x64, 0xD4);

  mouse_wait(1);
  outportb(0x60, a_write);
}

void mouse_install()
{
  uint8_t _status;
  mouse_wait(1);
  outportb(0x64, 0xA8);
 
  mouse_wait(1);
  outportb(0x64, 0x20);
  mouse_wait(0);
  _status=(inportb(0x60) | 2);
  mouse_wait(1);
  outportb(0x64, 0x60);
  mouse_wait(1);
  outportb(0x60, _status);
 

  mouse_write(0xF6);
  mouse_read();
 
  mouse_write(0xF4);
  mouse_read(); 

  irq_install_handler(12, handleMouse);
}