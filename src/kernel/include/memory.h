#ifndef MEMORY_H
#define MEMORY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint16_t PageDirectoryIndex; // Bit s 22 - 31
    uint16_t PageTableIndex; // Bits 12 - 21
    uint8_t PageAvailableBig; //Bits 11 - 8
    bool PageSize; // Bit 7 (0)
    bool PageAvailableSmall; // Bit 6
    bool PageAccessed; // Bit 5
    bool PageDisableCache; // Bit 4
    bool PageWriteThrough; // Bit 3
    bool PagePrivilegeLevel; // Controls Page Access for the Page, If the bit is set, it can be accessed by everyone but if the bit is not set, only the supervisor is able to access it | Bit 2
    bool PageEnableWrite; // Enables Read/Write if the bit is set, else the page is in read-only | Bit 1
    bool PageIsPresent; // Used to check if the Page is in physical memeory | Bit 0
} __attribute__((packed)) PageDirectorySmallEntry;

typedef struct {
    uint32_t PageMemoryAddress; // Bit 12 - 31
    uint8_t PageAvailable; // Bit 9 - 11
    bool PageGlobal; // Prevents the page from being invalidated by a MOV or CR3 instruction | Bit 8
    bool PageAttributeTable; // Reserved (0)
    bool PageDirty; // Used to check if the Desk has been written to | Bit 6
    bool PageAccessed; // Bit 5
    bool PageDisableCache; // Bit 4
    bool PageWriteThrough; // Bit 3
    bool PagePrivilegeLevel; // Controls Page Access for the Page, If the bit is set, it can be accessed by everyone but if the bit is not set, only the supervisor is able to access it | Bit 2
    bool PageEnableWrite; // Enables Read/Write if the bit is set, else the page is in read-only | Bit 1
    bool PageIsPresent; // Used to check if the Page is in physical memeory | Bit 0
} __attribute__((packed)) PageTableEntry;


#endif