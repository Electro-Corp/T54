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


; Flush segment registers
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