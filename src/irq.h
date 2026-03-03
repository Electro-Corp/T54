/*
    T54
    irq.c - Interrupt requests
*/
#ifndef IRQ_H
#define IRQ_H

#include "io.h"
#include "idt.h"

// Hold registers 
struct regs{
    unsigned int gs, fs, es, ds; // segment registers
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; 
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss; // processor pushes this for us
};

// Array of function pointers
static void* irq_routines[16] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

// irq_installHandler
// Installs custom handlers for an irq
void irq_installHandler(int irq, void (*handler)(struct regs *r));

// irq_removeHandler
// Clears the handler for specfied IRQ
void irq_removeHandler(int irq);

// irq_remap
// Since IRQs 0 to 8 are mapped to 8 to 15, we'd double fault
// in protected mode. Reprogram the PIC to map IRQ0-15 to IDT 32-47
void irq_remap();

// irq_install
// Remap the interrupt controllers, then install ISRs (like IDT and exception handlers)
void irq_install();

// irq_interruptHandler
// This is the function the IRQ ISRs point to. 
void irq_interruptHandler(struct regs *r);

#endif