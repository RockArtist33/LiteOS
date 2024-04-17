#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#define TIMER_ACCURACY 1193182

#ifndef TIMER_H
#define TIMER_H

uint64_t timerticks;

void init_Timer(uint32_t reload_value);
void timer_handler();
void sleep(uint32_t timeValue); // timevalue: Seconds

#endif