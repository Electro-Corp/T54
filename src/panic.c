/*
    T54
    panic.c - Kernel Panic 
*/

#include "video.h"

// List of exception names
unsigned char* exceptionMessages[] = {
    "Division by Zero",
    "Debug",
    "Non maskable interrupt",
    "Breakpoint",
    "Overflow detected",
    "Out of bounds",
    "Invalid opcode encountered",
    "No coprocessor",
    "Double Page Fault",
    "Coprocessor segment overrun",
    "Bad TSS",
    "Segment not present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
};

void kpanic(int int_no){
    // Out to serial should everything else die
    io_print("Kernel Panic: ");
    io_print(exceptionMessages[int_no]);
    // Video output
    v_kPanicScreen();
    v_terminalWrite("Kernel Panic: ");
    v_terminalWrite(exceptionMessages[int_no]);
    v_terminalWrite("!\nSystem halted. Restart to continue.\n====== Register Dump: ======\n");
    // insert dump here. . . .
    
    // In the future, depending on the error,
    // either allow for continued execution or
    // allow a debugger to connect
    v_setRow(24);
    v_setCol(0);
    v_terminalWrite("No debugger connected.\n");
    asm("hlt");
}