#include <stdint.h>
#include <serial.h>
#include <stdlib.h>
#include <gdt.h>


void setGdtEntry( uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
    GdtEntries[num].low_limt = (limit & 0xFFFF); // 16-bit
    GdtEntries[num].low_base = (base & 0xFFFF); // 16-bit
    GdtEntries[num].mid_base = ((base >> 16) & 0xFF); // 8-bit
    GdtEntries[num].access_byte = access; // 8-bit
    GdtEntries[num].flagsAndLimit = ((limit >> 16) & 0x0F); // 4-bit
    GdtEntries[num].flagsAndLimit |= (flags & 0xF0); // 4-bit
    GdtEntries[num].high_base = ((base >> 24) & 0xFF);
    
}

void setupGdt() {
    debugf("\n|------------------------ GDT SETUP ------------------------|\n");
    gdt_ptr.limit = GDT_ENTRIES_NUM * 8 - 1;
    gdt_ptr.base = (uint32_t)&GdtEntries;

    memset((uint8_t *)&tss, 0, sizeof(tss));
    tss.ss0 = 0x10;

    // GDT ENTRIES
    // ---------------------
    // NULL DESCRIPTOR
    // KERNEL CODE SEGMENT
    // KERNEL DATA SEGMENT
    // USER CODE SEGMENT
    // USER DATA SEGMENT
    // TASK STATE SEGMENT
    setGdtEntry(0, 0, 0, 0, 0);
    setGdtEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xC0);
    setGdtEntry(2, 0, 0xFFFFFFFF, 0x92, 0XC0);
    setGdtEntry(3, 0, 0xFFFFFFFF, 0xFA, 0xC0);
    setGdtEntry(4, 0, 0xFFFFFFFF, 0xF2, 0xC0);
    setGdtEntry(5, (uint32_t)&tss, sizeof(tss), 0x89, 0x40);
    
    debugf("[GDT] All gdt entries entered\n");
    
    gdt_flush((uint32_t)&gdt_ptr);
    tss_flush();

    debugf("[GDT] GDT has been flushed\n");
}