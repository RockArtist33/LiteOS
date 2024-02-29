#ifndef VGA_H
#define VGA_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

size_t strlen(const char* str);

void term_initialise(void);
void term_setcolor(uint8_t color);
void term_putchar(char c);
void term_write(const char* data, size_t size) ;
void term_writestring(const char* data);
void term_clear();
void term_newline();
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void disable_cursor();
void update_cursor(int x, int y);
uint16_t get_cursor_position(void);


#endif