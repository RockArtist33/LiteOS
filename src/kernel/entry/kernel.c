#include <stdint.h>
#include <gdt.h>
#include <isr.h>
#include <multiboot2.h>
#include <printf.h>
#include <serial.h>
#include <system.h>
#include <timer.h>
#include <vga.h>


#define MULTIBOOT2_MAGIC 0x36d76289

void ascii_title() {
    int timerval = 200;
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
    printf("==========================================\n\n");
}

void kernel_main(uint32_t magic, unsigned long mBInfoStructAddr) {
    term_initialise();
    if (!(magic == MULTIBOOT2_MAGIC)) {
        printf("[Multiboot] Incorrect Multiboot magic value: %x\n",magic);
        asm("hlt");
    }

    if (mBInfoStructAddr & 7) {
        printf("[Multiboot] Multiboot Info struct is unaligned\n");
        asm("hlt");
    }
    mBInfoStructSize = *(unsigned *)mBInfoStructAddr;
    mBInfoStruct = (struct multiboot_tag *)(mBInfoStructAddr + 8);
    uint32_t COM_PORT1 = 0x3F8;
    int result = init_serial(COM_PORT1);
    if (result != 0) {
        printf("[Serial] Serial port (0x%x) Failed to initialise: is faulty\n", COM_PORT1);
        printf("Result: %i", result);
        asm __volatile__ ("hlt");
    }

    debugf("#------------------------ DEBUG LOG ------------------------#\n");
    debugf("[Serial] Serial port 0x%x has been initialised successfully\n", COM_PORT1);
    debugf("[Multiboot] Multiboot2 has been reached:\n  - magic: 0x%x\n  - MultibootInfoStruct Address: 0x%x\n  - MultibootInfoStructSize: 0x%x\n", magic, mBInfoStructAddr, mBInfoStructSize);

    setupGdt();
    install_isr();
    init_Timer(1000);
    ascii_title();
}
