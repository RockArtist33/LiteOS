MBOOT_PAGE_ALIGN		equ 1 << 0
MBOOT_MEMINFO 			equ 1 << 1
; MBOOT_FLAGS 			equ MBOOT_PAGE_ALIGN | MBOOT_MEMINFO
MBOOT_ARCH				equ 0
MBOOT_MAGIC_NUMBER 		equ 0xE85250D6

section .multiboot2
header_start:
	dd 						MBOOT_MAGIC_NUMBER
	dd 						MBOOT_ARCH
	dd						header_end - header_start ; MBOOT_HEADER_SIZE
	dd 						0x100000000 - (MBOOT_MAGIC_NUMBER + MBOOT_ARCH + (header_end - header_start)) ; checksum

	dw 0 
	dw 0 
	dd 8
header_end:

section .bss
align 16
stack_bottom:
	resb 16384*8
stack_top:

section .text
extern kernel_main
global _start

_start:
	cli
	mov esp, stack_top
	push ebx
	push eax
	call kernel_main
	hlt

halt:
	hlt
	jmp halt
