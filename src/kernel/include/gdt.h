#ifndef GDT_H
#define GDT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define GDT_ENTRIES_NUM 6

typedef struct {
    uint16_t low_limt;
    uint16_t low_base;
    uint8_t  mid_base;
    uint8_t  access_byte;
    uint8_t  flagsAndLimit;
    uint8_t  high_base;
} __attribute__((packed)) GdtEntry;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) Gdt_Pointer;

typedef struct {
    uint16_t prev_task, prev_taks_reserved;
    uint32_t esp0;
    uint16_t ss0, _sso_reserved;
    uint32_t esp1;
    uint16_t ss1, _ss1_reserved;
    uint32_t esp2;
    uint16_t ss2, _ss2_reserved;
    uint32_t cr3;
    uint32_t eip, eflags, eax, ecx, edx, ebx, esx, ebp, esi, edi;
    uint16_t es, _es_reserved;
    uint16_t cs, _cs_reserved;
    uint16_t ss, _ss_reserved;
    uint16_t ds, _ds_reserved;
    uint16_t fs, _fs_reserved;
    uint16_t gs, _gs_reserved;
    uint16_t ldtr, _ldtr_reserved;
    uint16_t debug_flag, io_map;

} __attribute__((packed)) TSSEntry;


// Define a table to store GDT Entries
GdtEntry GdtEntries[GDT_ENTRIES_NUM];
Gdt_Pointer gdt_ptr;
TSSEntry tss;

void setupGdt();
void setGdtEntry(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
void gdt_flush(uint32_t addr);
void tss_flush();

#endif

