/**
 * T54
 * gdt.h - manages our GDT
 */
#ifndef GDT_H
#define GDT_H

// One GDT entry
struct gdt_entry{
    unsigned short limit_L;
    unsigned short base_L;
    unsigned char base_M;
    unsigned char access;
    unsigned char gran;
    unsigned char base_H;
} __attribute__((packed));

// Pointer with the limit (max bytes taken up by GDT - 1)
struct gdt_ptr{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

// gdt_setGate
// Set a desc in the GDT
void gdt_setGate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

// gdt_install
// Install our GDT
void gdt_install();

#endif