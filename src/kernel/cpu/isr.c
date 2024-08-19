#include <stdint.h>
#include <printf.h>
#include <system.h>
#include <timer.h>
#include <serial.h>
#include <isr.h>
#include <keyboard.h>

char *Exceptions[] = {
    "Divided by Zero",
    "Debug Exception called",
    "Detected a Non-maskable Interrupt",
    "Breakpoint has been reached",
    "Overflow when executing INTO instruction",
    "Out of Bounds",
    "Specified Opcode is invalid",
    "FPU device not available",
    "Double fault detected",
    "Coprocessor Segment Overrun",
    "Task State Segment is invalid",
    "Segment isnt available",
    "Stack fault detected",
    "General Protection Fault",
    "Page fault",
    "Reserved",
    "x87 Floating-point Exception detected",
    "Memeroy data reference is unaligned",
    "Machine check exception",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    "Reserved"
  };


void idt_set_descriptor(uint8_t num, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[num];
 
    descriptor->isr_low        = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08;
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
    debugf("\n|------------------------ ISR SETUP ------------------------|\n");
    remap_pic();
    debugf("[ISR] PIC remapped\n");

    idtr.base = (uint32_t)&idt;
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    for(uint8_t num = 0; num < 48; num++) {
        idt_set_descriptor(num, isr_code_table[num], 0x8E);
    }
    debugf("[ISR] IDT descriptors set\n");

    __asm__ volatile ("lidtl (%0)" : : "r"(&idtr));
    __asm__ volatile ("sti");
    debugf("[ISR] ISR Installed\n");

}

void exception_handler(AsmPassedInterrupt regs) {
  if (regs.interrupt >= 32 && regs.interrupt <= 47) { // IRQ
    if (regs.interrupt >= 40) {
      outportb(0xA0, 0x20);
    }
    outportb(0x20, 0x20);

    switch (regs.interrupt) {
    case 32:
      timer_handler();
      break;

    case 33:
      DetectIncomingChar();
      break;

    default:
      debugf("[ISR] interrupt code: %i\n", regs.interrupt);
      break;
    }
  } else if (regs.interrupt >= 0 && regs.interrupt <= 31) { // ISR
    printf("[ISR] Kernel Panic: %s!\n", Exceptions[regs.interrupt]);
    debugf("\n|---------------------- KERNEL PANIC -----------------------|\n");
    debugf("[ISR] Exception Detected: %s!\n", Exceptions[regs.interrupt]);
    asm("hlt");
  } else if (regs.interrupt == 0x80) {
    // reserved for syscall
  }
}