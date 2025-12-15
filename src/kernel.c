/*
    T54
    kernel.c - C entry point for kernel
*/
#include "video.h"
#include "memory.h"

// Test memory
void testMalloc();

void k_main(){
    v_initTerminal();
    v_terminalWrite("T54 v0.1\n");    
    
    // Load GDT
    v_terminalWrite("Loading GDT...");
    gdt_install();
    v_terminalWrite("GDT installed.\n");

    // Load IDT
    v_terminalWrite("Load IDT...");
    idt_install();
    v_terminalWrite("IDT loaded.\n");

    // Continue
    v_terminalWrite("The system is coming up, please wait.\n");

    testMalloc();

    v_terminalWrite("malloc() test concluded.\n");

    return 0;
}

void testMalloc(){
    // test malloc
    char* test = (char*)malloc(sizeof(char) * 16);
    test[0] = 'h';
    test[1] = 'i';
    test[2] = '!';
    test[3] = '\n';
    v_terminalWrite(test);

    char* test2 = (char*)malloc(sizeof(char) * 256);
    test2[0] = 'y';
    test2[1] = 'o';
    test2[2] = '\n';
    v_terminalWrite(test2);
}