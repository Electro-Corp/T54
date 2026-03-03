#include "irq.h"

// All of our ISRs
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

// irq_installHandler
// Installs custom handlers for an irq
void irq_installHandler(int irq, void (*handler)(struct regs *r)){
    irq_routines[irq] = handler;
}

// irq_removeHandler
// Clears the handler for specfied IRQ
void irq_removeHandler(int irq){
    irq_routines[irq] = 0;
}

// irq_remap
// Since IRQs 0 to 8 are mapped to 8 to 15, we'd double fault
// in protected mode. Reprogram the PIC to map IRQ0-15 to IDT 32-47
void irq_remap(){
    io_out(0x20, 0x11);
    io_out(0xA0, 0x11);
    io_out(0x21, 0x20);
    io_out(0xA1, 0x28);
    io_out(0x21, 0x04);
    io_out(0xA1, 0x02);
    io_out(0x21, 0x01);
    io_out(0xA1, 0x01);
    io_out(0x21, 0x0);
    io_out(0xA1, 0x0);
}

// irq_install
// Remap the interrupt controllers, then install ISRs (like IDT and exception handlers)
void irq_install(){
    irq_remap();

    idt_setGate(32, (unsigned)irq0, 0x08, 0x8E);
    idt_setGate(33, (unsigned)irq1, 0x08, 0x8E);
    idt_setGate(34, (unsigned)irq2, 0x08, 0x8E);
    idt_setGate(35, (unsigned)irq3, 0x08, 0x8E);
    idt_setGate(36, (unsigned)irq4, 0x08, 0x8E);
    idt_setGate(37, (unsigned)irq5, 0x08, 0x8E);
    idt_setGate(38, (unsigned)irq6, 0x08, 0x8E);
    idt_setGate(39, (unsigned)irq7, 0x08, 0x8E);
    idt_setGate(40, (unsigned)irq8, 0x08, 0x8E);
    idt_setGate(41, (unsigned)irq9, 0x08, 0x8E);
    idt_setGate(42, (unsigned)irq10, 0x08, 0x8E);
    idt_setGate(43, (unsigned)irq11, 0x08, 0x8E);
    idt_setGate(44, (unsigned)irq12, 0x08, 0x8E);
    idt_setGate(45, (unsigned)irq13, 0x08, 0x8E);
    idt_setGate(46, (unsigned)irq14, 0x08, 0x8E);
    idt_setGate(47, (unsigned)irq15, 0x08, 0x8E);
}


// irq_interruptHandler
// This is the function the IRQ ISRs point to. 
void irq_interruptHandler(struct regs *r){
    // Blank function pointer
    void (*handler)(struct regs *r);

    // Do we have a custom handler?
    handler = irq_routines[r->int_no - 32];
    if(handler) handler(r);

    // If IDT was greater than 40, send EOI so we can continue to get IRQs
    if(r->int_no >= 40){
        io_out(0xA0, 0x20);
    }

    // Send EOI to the controller anyway
    io_out(0x20, 0x20);
}