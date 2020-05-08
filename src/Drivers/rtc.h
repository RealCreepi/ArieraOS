#include "../common.h"
#include "../all_drivers.h"

int century_register;
unsigned char second;
unsigned char minute;
unsigned char hour;
unsigned char day;
unsigned char month;
unsigned char weekday;
unsigned int year;
unsigned char century;

int get_update_in_progress_flag();
unsigned char get_RTC_register(int reg);
void write_RTC_register(int reg, int data);

enum {
      cmos_address = 0x70,
      cmos_data    = 0x71
};

