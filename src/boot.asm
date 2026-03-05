;   
;   T54 Boot 
;   

MBALIGN equ 1 << 0 ; Align to page boundry
MEMINFO equ 1 << 1 ; Provide memory map (ha)
MBFLAGS equ MBALIGN  | MEMINFO ; multiboot flag
MAGIC equ 0x1BADB002 ; magic number
CHECKSUM equ -(MAGIC + MBFLAGS) ; checksum, trust us we're legit


; Actual multiboot header
section .multiboot
align 4
	dd MAGIC
	dd MBFLAGS
	dd CHECKSUM

; Our stack, multiboot standard doesn't provide us one
section .bss
align 16
stack_bottom: ; Grows down
resb 16384 ; 16kb stack
stack_top:


; Entry point for kernel (YAY)
section .text
global _start:function (_start.end - _start)
_start:
	; Setup stack
	mov esp, stack_top ; moved the esp to the top of the stack

	; jump to our C kernel
	extern k_main
	call k_main
	
	; out of k_main, just loop forever
	; disable interrupts
	cli
.hang:  
	hlt
	jmp .hang
.end:


; Flush segment registers and load GDT
global gdt_flush ; for C
extern gp ; from C
gdt_flush:
	cli
	lgdt [gp] ; load gdt from our pointer
	mov ax, 0x10 ; offset in gdt for our DATA segment
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax,
	mov ss, ax
	jmp 0x08:flush2
flush2:
	ret

; Load IDT
global idt_load ; for C
extern idt_p;
idt_load:
	lidt [idt_p]
	ret

; div 0 for testing
global div0
div0:
	mov ax, 100 
	mov bx, 0
	div bx


; ISR funcs

; C exception handler
extern isrs_faultHandle

; isr_commonStub
isr_commonStub:
	; Save processor states
	pusha
    push ds
    push es
    push fs
    push gs
	mov ax, 0x10 ; kernel segment descriptor
	mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp ; Push the stack
	push eax
	mov eax, isrs_faultHandle
	call eax ; preserve the eip register
	; Return registers to their previous states
	pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
	add esp, 8 ; clear error code
	iret ; pop cs, eip, eflags, ss, and esp

; this is kinda ugly and i wanna find a better solution later
global isr_0
global isr_1
global isr_2
global isr_3
global isr_4
global isr_5
global isr_6
global isr_7
global isr_8
global isr_9
global isr_10
global isr_11
global isr_12
global isr_13
global isr_14
global isr_15
global isr_16
global isr_17
global isr_18
global isr_19
global isr_20
global isr_21
global isr_22
global isr_23
global isr_24
global isr_25
global isr_26
global isr_27
global isr_28
global isr_29
global isr_30
global isr_31

; ISR 0
; Divide by 0
isr_0:
	cli
	push byte 0 ; no error code, so just push dummy 0 
				; to the stack
	push byte 0
	jmp isr_commonStub

; ISR 1
; Debug Exception
isr_1:
	cli
	push byte 0 ; no error code, so just push dummy 0 
				; to the stack
	push byte 1
	jmp isr_commonStub

; ISR 2
; Non maskable interrupt exception
isr_2:
	cli
	push byte 0 ; no error code, so just push dummy 0 
				; to the stack
	push byte 2
	jmp isr_commonStub

; ISR 3
; Breakpoint exception
isr_3:
	cli
	push byte 0 ; no error code, so just push dummy 0 
				; to the stack
	push byte 3
	jmp isr_commonStub

; ISR 4
; Detected Overflow exception
isr_4:
	cli
	push byte 0 ; no error code, so just push dummy 0 
				; to the stack
	push byte 4
	jmp isr_commonStub

; ISR 5
; Out of bounds exception
isr_5:
	cli
	push byte 0 ; no error code, so just push dummy 0 
				; to the stack
	push byte 5
	jmp isr_commonStub

; ISR 6
; Invalid opcode exception
isr_6:
	cli
	push byte 0 ; no error code, so just push dummy 0 
				; to the stack
	push byte 6
	jmp isr_commonStub

; ISR 7
; No coprocessor exception
isr_7:
	cli
	push byte 0 ; no error code, so just push dummy 0 
				; to the stack
	push byte 7
	jmp isr_commonStub

; ISR 8
; Double page fault 
isr_8:
	cli
	; dont push dummy, it does itself
	push byte 8
	jmp isr_commonStub

; ISR 9
; Coprocessor segment overrun  
isr_9:
	cli
	push byte 0
	push byte 9
	jmp isr_commonStub

; ISR 10
; Bad TSS exception  
isr_10:
	cli
	push byte 10
	jmp isr_commonStub

; ISR 11
; Segment Not Present exception  
isr_11:
	cli
	push byte 11
	jmp isr_commonStub

; ISR 12
; Stack Fault   
isr_12:
	cli
	push byte 12
	jmp isr_commonStub

; ISR 13
; General Protection Fault  
isr_13:
	cli
	push byte 13
	jmp isr_commonStub

; ISR 14
; Page Fault  
isr_14:
	cli
	push byte 14
	jmp isr_commonStub

; ISR 15
; Unknown Interrupt exception  
isr_15:
	cli
	push byte 0
	push byte 15
	jmp isr_commonStub

; ISR 16
; Coprocessor Fault
isr_16:
	cli
	push byte 0
	push byte 16
	jmp isr_commonStub

; ISR 17
; Alignment Check exception
isr_17:
	cli
	push byte 0
	push byte 17
	jmp isr_commonStub

; ISR 18
; Machine Check Exception
isr_18:
	cli
	push byte 0
	push byte 18
	jmp isr_commonStub

; ISR 19
; Reserved Exception
isr_19:
	cli
	push byte 0
	push byte 19
	jmp isr_commonStub

; ISR 20
; Reserved Exception
isr_20:
	cli
	push byte 0
	push byte 20
	jmp isr_commonStub

; ISR 21
; Reserved Exception
isr_21:
	cli
	push byte 0
	push byte 21
	jmp isr_commonStub

; ISR 22
; Reserved Exception
isr_22:
	cli
	push byte 0
	push byte 22
	jmp isr_commonStub

; ISR 23
; Reserved Exception
isr_23:
	cli
	push byte 0
	push byte 23
	jmp isr_commonStub

; ISR 24
; Reserved Exception
isr_24:
	cli
	push byte 0
	push byte 24
	jmp isr_commonStub

; ISR 25
; Reserved Exception
isr_25:
	cli
	push byte 0
	push byte 25
	jmp isr_commonStub

; ISR 26
; Reserved Exception
isr_26:
	cli
	push byte 0
	push byte 26
	jmp isr_commonStub

; ISR 27
; Reserved Exception
isr_27:
	cli
	push byte 0
	push byte 27
	jmp isr_commonStub

; ISR 28
; Reserved Exception
isr_28:
	cli
	push byte 0
	push byte 28
	jmp isr_commonStub

; ISR 29
; Reserved Exception
isr_29:
	cli
	push byte 0
	push byte 29
	jmp isr_commonStub

; ISR 30
; Reserved Exception
isr_30:
	cli
	push byte 0
	push byte 30
	jmp isr_commonStub

; ISR 31
; Reserved Exception
isr_31:
	cli
	push byte 0
	push byte 31
	jmp isr_commonStub


;
; IRQ, interrupt requests 
;
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

; IRQ 0
irq0:
	cli
	push byte 0 
	push byte 32
	jmp irq_commonStub

; IRQ 1
irq1:
	cli
	push byte 0 
	push byte 33
	jmp irq_commonStub

; IRQ 2
irq2:
	cli
	push byte 0 
	push byte 34
	jmp irq_commonStub

; IRQ 3
irq3:
	cli
	push byte 0 
	push byte 35
	jmp irq_commonStub

; IRQ 4
irq4:
	cli
	push byte 0 
	push byte 36
	jmp irq_commonStub

; IRQ 5
irq5:
	cli
	push byte 0 
	push byte 37
	jmp irq_commonStub

; IRQ 6
irq6:
	cli
	push byte 0 
	push byte 38
	jmp irq_commonStub

; IRQ 7
irq7:
	cli
	push byte 0 
	push byte 39
	jmp irq_commonStub

; IRQ 8
irq8:
	cli
	push byte 0 
	push byte 40
	jmp irq_commonStub

; IRQ 9
irq9:
	cli
	push byte 0 
	push byte 41
	jmp irq_commonStub


; IRQ 10
irq10:
	cli
	push byte 0 
	push byte 42
	jmp irq_commonStub


; IRQ 11
irq11:
	cli
	push byte 0 
	push byte 43
	jmp irq_commonStub

; IRQ 12
irq12:
	cli
	push byte 0 
	push byte 44
	jmp irq_commonStub

; IRQ 13
irq13:
	cli
	push byte 0 
	push byte 45
	jmp irq_commonStub

; IRQ 14
irq14:
	cli
	push byte 0 
	push byte 46
	jmp irq_commonStub

; IRQ 15
irq15:
	cli
	push byte 0 
	push byte 47
	jmp irq_commonStub

; Extern function for interrupts in irq.c
extern irq_interruptHandler

; Stub handler, will call func
irq_commonStub:
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp
	push eax
	mov eax, irq_interruptHandler
	call eax
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret

;
; Enter user mode
;
global jumpToUserMode

jumpToUserMode_old:
	cli
	mov eax, [esp+4] ; entry
	mov edx, [esp+8] ; stack
	push 0x20
	push edx
	pushf ; 
	push (3 * 8) | 3
	push eax
	iret

jumpToUserMode:
	mov ax, (4 * 8) | 3
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov eax, esp
	push (4 * 8) | 3
	pushf
	push (3 * 8) | 3
	mov ebx, [esp+4]
	push ebx
	iret