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
    
    dev_initStorageDevices();

    v_terminalWrite("-----------------------------------------------\n");

    v_terminalWrite("===== Root FS selection =====\n");
    // Once keyboard input works, detect drives and
    // have the user select the boot media
    // until then, just assume CD-ROM
    v_terminalWrite("[ X ]      CD-ROM\n");  
    v_terminalWrite("[   ]      HDD\n");    
    v_terminalWrite("=============================\n");

    // Initilize the file system
    fs_init(dev_getStorageDeviceWithIndex(0));

    // Load init program
    v_terminalWrite("[Kernel] Loading T54 init program from \"CD-ROM\"...\n");

    while(1){
        int c = keyboard_popLastChar();
        if(c > 0) v_terminalPushChar(c);
    }
}