#ifndef ISR_H
#define ISR_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define IDT_MAX_DESCRIPTORS 256
typedef struct {
  // pushed by us:
  uint32_t gs, fs, es, ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // esp is ignored
  uint32_t interrupt, error;

  // pushed by the CPU:
  uint32_t eip, cs, eflags, usermode_esp, usermode_ss;
} AsmPassedInterrupt;

typedef struct {
	uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t     reserved;     // Set to zero
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

typedef struct {
	uint16_t	limit;
	uint32_t	base;
} __attribute__((packed)) idtr_t;

static idt_entry_t idt[IDT_MAX_DESCRIPTORS];
static idtr_t idtr;
extern void* isr_code_table[];

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void install_isr(); // WORK
void exception_handler();

#endif