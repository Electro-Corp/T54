section .text

extern keyboard_handler
global read_port
global write_port
global load_idt
global keyboard_handler_int

keyboard_handler_int:
    pushad
    cld
    call keyboard_handler
    popad
    iretd

load_idt:
    mov edx, [esp + 4]
    lidt [edx]
    sti
    ret

; arg: int, port number.
read_port:
    mov edx, [esp + 4]
    in al, dx
    ret

; arg: int, (dx)port number
;      int, (al)value to write
write_port:
    mov   edx, [esp + 4]
    mov   al, [esp + 4 + 4]
    out   dx, al
    ret
extern exception_handler
isr_no_err_stub0
isr_no_err_stub1
isr_no_err_stub2
isr_no_err_stub3
isr_no_err_stub4
isr_no_err_stub5
isr_no_err_stub6
isr_no_err_stub7
isr_err_stub8
isr_no_err_stub9
isr_err_stub10
isr_err_stub11
isr_err_stub12
isr_err_stub13
isr_err_stub14
isr_no_err_stub15
isr_no_err_stub16
isr_err_stub17
isr_no_err_stub18
isr_no_err_stub19
isr_no_err_stub20
isr_no_err_stub21
isr_no_err_stub22
isr_no_err_stub23
isr_no_err_stub24
isr_no_err_stub25
isr_no_err_stub26
isr_no_err_stub27
isr_no_err_stub28
isr_no_err_stub29
isr_err_stub30
isr_no_err_stub31
global isr_stub_table
isr_stub_table:
%assign i 0 
%rep    32 
    dd "isr_stub_"+i ; use DQ instead if targeting 64-bit
%assign i i+1 
%endrep


%macro isr_err_stub 1
isr_stub_%+%1:
    call exception_handler
    iret 
%endmacro
; if writing for 64-bit, use iretq instead
%macro isr_no_err_stub 1
isr_stub_%+%1:
    call exception_handler
    iret
%endmacro
