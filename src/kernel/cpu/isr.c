#include <stdint.h>
#include <system.h>
#include <isr.h>


void idt_set_descriptor(uint8_t num, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[num];
 
    descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
    descriptor->attributes     = flags;
    descriptor->isr_high       = (uint32_t)isr >> 16;
    descriptor->reserved       = 0;
}
void remap_pic() {
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x00);
    outportb(0xA1, 0x00);
}

void install_isr() {
    remap_pic();

    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    for(uint8_t num = 0; num < 32; num++) {
        idt_set_descriptor(num, isr_code_table[num], 0x8E);
    }

    __asm__ volatile ("lidt %0" : : "m"(idtr));
    __asm__ volatile ("sti");

}

void exception_handler() {

    __asm__ volatile ("cli; hlt"); // Completely hangs the computer
}