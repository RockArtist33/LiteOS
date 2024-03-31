#ifndef GDT_H
#define GDT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define GDT_ENTRIES_NUM 8

typedef struct GdtEntry {
    uint16_t low_limt;
    uint16_t low_base;
    uint8_t  mid_base;
    uint8_t  access_byte;
    uint8_t  flagsAndLimit;
    uint8_t  high_base;
} __attribute__((packed)) GdtEntry;

typedef struct Gdt_Pointer {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) Gdt_Pointer;

// Define a table to store GDT Entries
GdtEntry GdtEntries[GDT_ENTRIES_NUM];
Gdt_Pointer gdt_ptr;

void setupGdt();
void setGdtEntry(uint32_t num, uint32_t limit, uint32_t base, uint8_t access, uint8_t flags);
void gdt_flush(uint32_t addr);

#endif

