/*
    T54
    kernel.c - C entry point for kernel
*/
#include "video.h"
#include "memory.h"

// Devices
#include "drivers/cdrom.h"

// Test malloc
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

    testMalloc();
    v_terminalWrite("malloc() test concluded.\n");

    v_terminalWrite("===== Root FS selection =====\n");
    // Once keyboard input works, detect drives and
    // have the user select the boot media
    // until then, just assume CDrom
    v_terminalWrite("[ X ]     CD-ROM\n");  
    v_terminalWrite("[   ]     HDD\n");    
    v_terminalWrite("=============================\n");
    v_terminalWrite("Loading T54 init program from \"CD-ROM!\"\n");


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

    // Now that we freed some memory.. 
    // lets try and reallocate and see if we get that 
    // memory again
    const char* a3 = "Realloc attempt.\n";
    char* test3 = (char*)malloc(sizeof(char) * strlen(a3));
    memcpy(a3, test3, strlen(a3));
    v_terminalWrite(test3);
    free(a3);
}