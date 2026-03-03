/*
    T54 
    idt.h - manages the Interrupt Descriptor Table
*/
#ifndef IDT_H
#define IDT_H

#include "std/stdlib.h"

struct idt_entry{
    unsigned short base_L;
    unsigned short sel; // kernel segment here
    unsigned char zero; // i wonder what this will be set to
    unsigned char flags;
    unsigned short base_H;
} __attribute__((packed));

struct idt_ptr{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

// idt_setGate
// Set entry within IDT
void idt_setGate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);

// idt_install
// Install the IDT and create ISRs
void idt_install();

#endif