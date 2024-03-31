#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <printf.h>
#include <system.h>

enum vga_color {
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_LIGHT_BROWN = 14,
    COLOR_WHITE = 15,
};


static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
    return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

static const size_t VGA_WIDTH=80;
static const size_t VGA_HEIGHT=25;
size_t row;
size_t column;
uint8_t term_color;
uint16_t* term_buffer;
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outportb(0x3D4, 0x0A);
	outportb(0x3D5, (inportb(0x3D5) & 0xC0) | cursor_start);
 
	outportb(0x3D4, 0x0B);
	outportb(0x3D5, (inportb(0x3D5) & 0xE0) | cursor_end);
}

void disable_cursor()
{
	outportb(0x3D4, 0x0A);
	outportb(0x3D5, 0x20);
}

void term_initialise(void)
{
    row = 0;
    column = 0;
    enable_cursor(0,15);
    term_color = vga_entry_color(COLOR_WHITE, COLOR_BLACK);
    term_buffer = (uint16_t*) 0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            term_buffer[index] = vga_entry(' ', term_color);
        }
    }
    
}

void term_setcolor(uint8_t color)
{
    term_color = color;
}

void update_cursor(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;
 
	outportb(0x3D4, 0x0F);
	outportb(0x3D5, (uint8_t) (pos & 0xFF));
	outportb(0x3D4, 0x0E);
	outportb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

uint16_t get_cursor_position(void)
{
    uint16_t pos = 0;
    outportb(0x3D4, 0x0F);
    pos |= inportb(0x3D5);
    outportb(0x3D4, 0x0E);
    pos |= ((uint16_t)inportb(0x3D5)) << 8;
    return pos;
}

void term_clear()
{
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            term_buffer[index] = vga_entry(' ', term_color);
        }
    }
}
void term_newline(){
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            term_buffer[index] = term_buffer[index+VGA_WIDTH];
        }
    }
}

void term_putentryat(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    term_buffer[index] = vga_entry(c, color);
}

void term_putchar(char c)
{
    if (c == '\n'){
        row +=1;
        if (row == VGA_HEIGHT){
            term_newline();
            row = VGA_HEIGHT-1;
        }
        column = 0;
        update_cursor(column, row);
        return;
    }
    if (c == '^') {
        if (--column < 0) {
          row -=1;
          column = VGA_WIDTH-1; 
        }
        term_putentryat(' ', term_color, column, row);
        update_cursor(column, row);
        return;
    }
    term_putentryat(c, term_color, column, row);
    if(++column == VGA_WIDTH){
        column = 0;
        if (++row == VGA_HEIGHT){
            term_newline();
            row = VGA_HEIGHT-1;
        }
    }
    update_cursor(column,row);
}

void term_write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++){
        term_putchar(data[i]);
    }
}

void term_writestring(const char* data)
{
    term_write(data, strlen(data));
}

