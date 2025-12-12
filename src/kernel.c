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

    // Continue
    v_terminalWrite("System is coming up, please wait.");

    

    return 0;
}