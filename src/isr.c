/*
    T54
    isr.c - isr's for interrupts
*/

// Externs to the functions from ASM
// ugly i know
extern void isr_0();
extern void isr_1();
extern void isr_2();
extern void isr_3();
extern void isr_4();
extern void isr_5();
extern void isr_6();
extern void isr_7();
extern void isr_8();
extern void isr_9();
extern void isr_10();
extern void isr_11();
extern void isr_12();
extern void isr_13();
extern void isr_14();
extern void isr_15();
extern void isr_16();
extern void isr_17();
extern void isr_18();
extern void isr_19();
extern void isr_20();
extern void isr_21();
extern void isr_22();
extern void isr_23();
extern void isr_24();
extern void isr_25();
extern void isr_26();
extern void isr_27();
extern void isr_28();
extern void isr_29();
extern void isr_30();
extern void isr_31();

// Hold registers so we can read on an exception
struct regs{
    unsigned int gs, fs, es, ds; // segment registers
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax; 
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss; // processor pushes this for us
};

// isrs_install
// annoying function that loads our isr's
void isrs_install(){
    // 1s
    idt_setGate(0, (unsigned)isr_0, 0x08, 0x8E);
    idt_setGate(1, (unsigned)isr_1, 0x08, 0x8E);
    idt_setGate(2, (unsigned)isr_2, 0x08, 0x8E);
    idt_setGate(3, (unsigned)isr_3, 0x08, 0x8E);
    idt_setGate(4, (unsigned)isr_4, 0x08, 0x8E);
    idt_setGate(5, (unsigned)isr_5, 0x08, 0x8E);
    idt_setGate(6, (unsigned)isr_6, 0x08, 0x8E);
    idt_setGate(7, (unsigned)isr_7, 0x08, 0x8E);
    idt_setGate(8, (unsigned)isr_8, 0x08, 0x8E);
    idt_setGate(9, (unsigned)isr_9, 0x08, 0x8E);
    // 10s
    idt_setGate(10, (unsigned)isr_10, 0x08, 0x8E);
    idt_setGate(11, (unsigned)isr_11, 0x08, 0x8E);
    idt_setGate(12, (unsigned)isr_12, 0x08, 0x8E);
    idt_setGate(13, (unsigned)isr_13, 0x08, 0x8E);
    idt_setGate(14, (unsigned)isr_14, 0x08, 0x8E);
    idt_setGate(15, (unsigned)isr_15, 0x08, 0x8E);
    idt_setGate(16, (unsigned)isr_16, 0x08, 0x8E);
    idt_setGate(17, (unsigned)isr_17, 0x08, 0x8E);
    idt_setGate(18, (unsigned)isr_18, 0x08, 0x8E);
    idt_setGate(19, (unsigned)isr_19, 0x08, 0x8E);
    // 20s
    idt_setGate(20, (unsigned)isr_20, 0x08, 0x8E);
    idt_setGate(21, (unsigned)isr_21, 0x08, 0x8E);
    idt_setGate(22, (unsigned)isr_22, 0x08, 0x8E);
    idt_setGate(23, (unsigned)isr_23, 0x08, 0x8E);
    idt_setGate(24, (unsigned)isr_24, 0x08, 0x8E);
    idt_setGate(25, (unsigned)isr_25, 0x08, 0x8E);
    idt_setGate(26, (unsigned)isr_26, 0x08, 0x8E);
    idt_setGate(27, (unsigned)isr_27, 0x08, 0x8E);
    idt_setGate(28, (unsigned)isr_28, 0x08, 0x8E);
    idt_setGate(29, (unsigned)isr_29, 0x08, 0x8E);
    // 30s
    idt_setGate(30, (unsigned)isr_30, 0x08, 0x8E);
    idt_setGate(31, (unsigned)isr_31, 0x08, 0x8E);
}


// isrs_faultHandle
// Handle a fault
void isrs_faultHandle(struct regs* r){
    if(r->int_no < 32){
        kpanic(r->int_no);
    }
}