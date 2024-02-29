#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void io_wait(void);
void outportb(uint16_t port, uint8_t val);
uint8_t inportb(uint16_t port);

#endif