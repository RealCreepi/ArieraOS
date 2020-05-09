#pragma once

extern unsigned long timer_ticks;

void task_add(void* func, int interval);
void task_remove(int position);

void timer_wait(int ms);
void timer_install(uint32_t frequency);
unsigned long get_timer_ticks();