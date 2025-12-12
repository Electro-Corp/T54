/*
    T54 
    idt.c - manages the Interrupt Descriptor Table
*/
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

// IDT with 256 entries 
struct idt_entry idt[256];
struct idt_ptr idt_p;

// ASM function to load our IDT
extern void idt_load();

// idt_setGate
// Set entry within IDT
void idt_setGate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags){
    // Base L and H
    idt[num].base_L = (base & 0xFFFF);
    idt[num].base_H = ((base >> 16) & 0xFFFF);
    // Set 0
    idt[num].zero = 0;
    // Set kernel segment
    idt[num].sel = sel;
    // Set flags
    idt[num].flags = flags;
}

// idt_install
// Install the IDT and create ISRs
void idt_install(){
    idt_p.limit = (sizeof(struct idt_entry) * 256) - 1;
    idt_p.base = &idt;

    // Clear out entire IDT
    memset(&idt, 0 , sizeof(struct idt_entry) * 256);

    // Create ISRs
    isrs_install();

    // Point CPU to our IDT
    idt_load();
}