/*
    T54
    kernel.c - C entry point for kernel
*/
#include "video.h"

void k_main(){
    v_initTerminal();
    v_terminalWrite("T54 v0.1\n");    
    
    // Load GDT
    v_terminalWrite("Loading GDT...\n");
    gdt_install();
    v_terminalWrite("GDT installed.\n");

    // Load IDT
    v_terminalWrite("Load IDT...\n");
    idt_install();
    v_terminalWrite("IDT loaded.\n");

    // Continue
    v_terminalWrite("The system is coming up, please wait.\n");    

    extern void div0();
    div0();

    return 0;
}