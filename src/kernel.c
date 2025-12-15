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
    const char* a1 = "Testing malloc, this is string one.\n";
    const char* a2 = "Continuing the test, this is string two.\n";
    char* test = (char*)malloc(sizeof(char) * strlen(a1));
    memcpy(a1, test, strlen(a1));
    v_terminalWrite(test);

    char* test2 = (char*)malloc(sizeof(char) * strlen(a2));
    memcpy(a2, test2, strlen(a2));
    v_terminalWrite(test2);

    // free them, we're done
    free(test);
    free(test2);
}