global isr_wrapper
align 4
isr_wrapper:
    pushad
    cld
    ;mov [0xb8000], 0x07690748
    extern gpfExcHandler    
    call gpfExcHandler
    popad
    ;iret

