#include <stdint.h>
#include <gdt.h>

void setGdtEntry( uint32_t num, uint32_t limit, uint32_t base, uint8_t access, uint8_t flags)
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
    gdt_ptr.limit = GDT_ENTRIES_NUM * 8 - 1;
    gdt_ptr.base = (uint32_t)&GdtEntries;
    // GDT ENTRIES
    // ---------------------
    // NULL DESCRIPTOR
    // KERNEL CODE SEGMENT
    // KERNEL DATA SEGMENT
    // USER CODE SEGMENT
    // USER DATA SEGMENT
    // TASK STATE SEGMENT - NOT IMPLEMENTED
    setGdtEntry(0, 0, 0, 0, 0);
    setGdtEntry(1, 0xFFFFF, 0, 0x9A, 0xC);
    setGdtEntry(2, 0xFFFFF, 0, 0x92, 0XC);
    setGdtEntry(3, 0xFFFFF, 0, 0xFA, 0xC);
    setGdtEntry(4, 0xFFFFF, 0, 0xF2, 0xC);
    //setGdtEntry(5, (uint32_t)&tss, sizeof(tss), 0x89, 0x40);
    gdt_flush((uint32_t)&gdt_ptr);
}