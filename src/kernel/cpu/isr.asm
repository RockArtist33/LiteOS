
isr_common:
    ; push registers to match struct AsmPassedInterrupt (little endian)
    pushad
    push ds
    push es
    push fs
    push gs

    ; load kernel data segment
    push ebx
    mov bx, 0x10
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    pop ebx

    extern exception_handler
    call exception_handler

    pop gs
    pop fs
    pop es
    pop ds
    popad
    add esp, 8
    iret

%macro isr_err_code 1
isr_code_%+%1:
    push dword %1
    jmp isr_common
%endmacro
; if writing for 64-bit, use iretq instead
%macro isr_no_err_code 1
isr_code_%+%1:
    push dword %0
    push dword %1
    jmp isr_common
%endmacro


isr_no_err_code 0
isr_no_err_code 1
isr_no_err_code 2
isr_no_err_code 3
isr_no_err_code 4
isr_no_err_code 5
isr_no_err_code 6
isr_no_err_code 7
isr_err_code    8
isr_no_err_code 9
isr_err_code    10
isr_err_code    11
isr_err_code    12
isr_err_code    13
isr_err_code    14
isr_no_err_code 15
isr_no_err_code 16
isr_err_code    17
isr_no_err_code 18
isr_no_err_code 19
isr_no_err_code 20
isr_no_err_code 21
isr_no_err_code 22
isr_no_err_code 23
isr_no_err_code 24
isr_no_err_code 25
isr_no_err_code 26
isr_no_err_code 27
isr_no_err_code 28
isr_no_err_code 29
isr_err_code    30
isr_no_err_code 31

; Interupt Requests (IRQS)
; All IRQS 0 to 15 are mapped to 32 - 47
isr_no_err_code 32 ; Programmable Interval Timer (PIT)
isr_no_err_code 33
isr_no_err_code 34
isr_no_err_code 35
isr_no_err_code 36
isr_no_err_code 37
isr_no_err_code 38
isr_no_err_code 39
isr_no_err_code 40
isr_no_err_code 41
isr_no_err_code 42
isr_no_err_code 43
isr_no_err_code 44
isr_no_err_code 45
isr_no_err_code 46
isr_no_err_code 47

global isr_code_table
isr_code_table:
%assign i 0 
%rep    48
    dd isr_code_%+i ; use DQ instead if targeting 64-bit
%assign i i+1 
%endrep