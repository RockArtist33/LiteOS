extern exception_handler

%macro isr_err_code 1
isr_code_%+%1:
    call exception_handler
    iret 
%endmacro
; if writing for 64-bit, use iretq instead
%macro isr_no_err_code 1
isr_code_%+%1:
    call exception_handler
    iret
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

global isr_code_table
isr_code_table:
%assign i 0 
%rep    32 
    dd isr_code_%+i ; use DQ instead if targeting 64-bit
%assign i i+1 
%endrep