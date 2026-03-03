/*
    T54
    kernel.c - C entry point for kernel
*/
#include "video.h"
#include "memory.h"
#include "idt.h"
#include "gdt.h"
#include "irq.h"
#include "fs/fs.h"
#include "drivers/devices.h"

// Devices
#include "drivers/cdrom.h"
#include "drivers/keyboard.h"


void k_main(){
    v_initTerminal();
    v_terminalWrite("T54 Kernel Version 0.1.17\n");
    v_terminalWrite("(c) 2025-2026 Electro-Corp, All Rights Reserved\n");
    v_terminalWrite("-----------------------------------------------\n");
    
    // Load GDT
    v_terminalWrite("[Kernel] Loading GDT...");
    gdt_install();
    v_terminalWrite("GDT installed.\n");

    // Load IDT
    v_terminalWrite("[Kernel] Loading IDT...");
    idt_install();
    v_terminalWrite("IDT loaded.\n");

    // Init IRQs
    irq_install();
    // Initilize the keyboard
    irq_installHandler(1, keyboard_handleInterrupt);
    __asm__ __volatile__ ("sti"); 
    
    // Initilize storage devices
    dev_initStorageDevices();

    v_terminalWrite("-----------------------------------------------\n");

    // Root selection
    v_terminalWrite("===== Root FS selection =====\n");
    v_terminalWrite("[ X ]      CD-ROM\n");  
    v_terminalWrite("[   ]      HDD\n");    
    v_terminalWrite("=============================\n");
    v_terminalWrite("\'w\', \'s\' and ENTER...\n");
    // Save position of items
    int cdSel = v_getRow() - 4, draw = 0, idx = 0, done = 0;
    while(!done){
        draw = 0;
        int c = keyboard_popLastChar();
        switch(c){
            case 's':
                if(idx < 1) idx++;
                draw = 1;
                break;
            case 'w':
                if(idx > 0) idx--;
                draw = 1;
                break;
            case '\n':
                done = 1;
                draw = 1;
                break;
        }
        // Render if needed
        if(draw){
            v_setRow(cdSel);
            if(idx == 0) v_terminalWrite("[ X ]      CD-ROM\n");
            else   v_terminalWrite("[   ]      CD-ROM\n");
            v_setRow(cdSel + 1);
            if(idx == 1) v_terminalWrite("[ X ]      HDD\n");
            else   v_terminalWrite("[   ]      HDD\n");
        }
    }
    // Reset row
    v_setRow(cdSel + 5);

    // Initilize the file system
    fs_init(dev_getStorageDeviceWithIndex(idx));

    // Load init program
    v_terminalWrite("[Kernel] Loading T54 init program from \"CD-ROM\"...\n");

    while(1){
        int c = keyboard_popLastChar();
        if(c > 0){
            v_terminalPushChar(c);
            v_updateCursor();
        }
    }
}