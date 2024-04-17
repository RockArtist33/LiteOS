#include <stdint.h>
#include <gdt.h>
#include <isr.h>
#include <multiboot2.h>
#include <ps2.h>
#include <printf.h>
#include <serial.h>
#include <system.h>
#include <timer.h>
#include <vga.h>


#define MULTIBOOT2_MAGIC 0x36d76289

void ascii_title() {
    term_clear();
    printf("==========================================\n");
    printf("|                                        |\n");
    printf("|                                        |\n");
    printf("|    _      _  _           ___   ____    |\n");
    printf("|   | |    (_)| |_   ___  / _ \\ / ___|   | \n");
    printf("|   | |    | || __| / _ \\| | | |\\___ \\   | \n");
    printf("|   | |___ | || |_ |  __/| |_| | ___) |  |\n");
    printf("|   |_____||_| \\__| \\___| \\___/ |____/   |\n");
    printf("|                                        |\n");
    printf("|             Version: 0.0.1             |\n");
    printf("|                                        |\n");
    printf("==========================================   \n\n");
}

void kernel_main(uint32_t magic, unsigned long mBInfoStructAddr) {
    term_initialise();
    if (!(magic == MULTIBOOT2_MAGIC)) {
        printf("[Multiboot] Incorrect Multiboot magic value: %x\n",magic);
        asm("hlt");
    }

    if (mBInfoStructAddr & 7) {
        printf("[Multiboot] Multiboot Info struct is unaligned");
        asm("hlt");
    }
    
    mBInfoStructSize = *(unsigned *)mBInfoStructAddr;
    mBInfoStruct = (struct multiboot_tag *)(mBInfoStructAddr + 8);
    uint32_t COM_PORT1 = 0x3F8;
    if (init_serial(COM_PORT1) != 0) {
        debugf("[Serial] Serial port (%x) Failed to initialise: is faulty\n");
    }

    debugf("[Serial] Serial port %x has been initialised successfully\n", COM_PORT1);
    debugf("[Multiboot] Multiboot2 has been reached:\n  - magic: %x\n  - MultibootInfoStruct Address: %x\n  - MultibootInfoStructSize: %x\n", magic, mBInfoStructAddr, mBInfoStructSize);

    setupGdt();
    install_isr();
    init_Timer(1000);

    printf("[NOTE] Kernel Initialisation complete, starting shell.\n");
    sleep(1);
    ascii_title();
    int num = 0;
    num = num / 0;
    int color;
    /*
    int fg;
    fg = 15;
    for (int i = 0; i < 16; i++){
        color = (fg | i << 4);
        term_setcolor(color);
        printf("        ");
        if (((i+1) % 4 == 0)) {
            printf("\n");
        }
    }
    for (int i = 0; i < 16; i++){
        color = (fg-i | i << 4);
        term_setcolor(color);
        printf("ABCDEFGH");
        if (((i+1) % 4 == 0)) {
            printf("\n");
        }
    }
    term_setcolor(0x0F);
    */
    while (true) {
        sleep(1);
        num++;
        printf("[test] %i seconds\n", num);
    }

    
    
    
    
}
