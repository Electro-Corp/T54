/*
    T54
    kernel.c - C entry point for kernel
*/
#include "video.h"
#include "paging.h"
#include "memory.h"
#include "idt.h"
#include "gdt.h"
#include "irq.h"
#include "proc.h"
#include "io.h"
#include "fs/fs.h"
#include "drivers/devices.h"

// Devices
#include "drivers/cdrom.h"
#include "drivers/keyboard.h"

// Root device selection
int renderRootDeviceSelector();

void k_main(){
    io_print("T54 Serial Communications initilized.\n");
    v_initTerminal();
    v_terminalWrite("T54 Kernel Version 0.1.1 (Built @ ");
    v_terminalWrite(__TIME__);
    v_terminalWrite(")\n");
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

    // Initilize paging
    paging_mapFirst4MB();
    paging_enablePaging();
        
    // Initilize storage devices
    dev_initStorageDevices();

    v_terminalWrite("-----------------------------------------------\n");

    // Root selection
    v_terminalWrite("===== Root FS selection =====\n");
    v_terminalWrite("[ X ]      CD-ROM\n");  
    v_terminalWrite("[   ]      HDD\n");    
    v_terminalWrite("=============================\n");
    v_terminalWrite("\'w\', \'s\' and ENTER...\n");
    
    int devId = renderRootDeviceSelector();

    // Initilize the file system
    fs_init(dev_getStorageDeviceWithIndex(devId));
    
    // Open a test ELF
    int testELFHandle = fs_openFile("/bin/test.");
    uint8_t* program = (uint8_t*)kmalloc(sizeof(uint8_t) * 336);
    int g = fs_readFile(testELFHandle, program, 336);
    if(g < 0){
        switch(testELFHandle){
            case FILE_NOT_FOUND:
                v_terminalWrite("FILE_NOT_FOUND\n");
                break;
            case TRIED_TO_OPEN_DIRECTORY:
                v_terminalWrite("TRIED_TO_OPEN_DIRECTORY\n");
                break;
            case INVALID_FS_HANDLE:
                v_terminalWrite("INVALID_FS_HANDLE\n");
                break;
            case INVALID_IMPL_HANDLE:
                v_terminalWrite("INVALID_IMPL_HANDLE\n");
                break;
        }
    }else{
        proc_loadProgram(program);
    }
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


// Root device selection
int renderRootDeviceSelector(){
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
    return idx;
}