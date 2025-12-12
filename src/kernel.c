/*
    T54
    kernel.c - C entry point for kernel
*/
#include "video.h"

void k_main(){
    v_initTerminal();
    v_terminalWrite("T54 v0.1");
    
    // Load GDT
    v_terminalWrite("Loading GDT...");
    gdt_install();
    v_terminalWrite("GDT installed.");

    // Load IDT
    v_terminalWrite("Load IDT...");
    idt_install();
    v_terminalWrite("IDT loaded.");

    // Continue
    v_terminalWrite("The system is coming up, please wait.");

    extern void div0();

    div0();
    

    return 0;
}