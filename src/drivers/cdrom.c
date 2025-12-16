#include "cdrom.h"

int cdrom_detectDrive(){
    // To detect an ATAPI drive, we can read a few
    // registers and see if what we get back
    // We're only (currently) interested in packet devices
    unsigned char reg1, reg2, reg3, reg4;
    // Read the registers
    reg1 = io_in(0x1F2);
    reg2 = io_in(0x1F3);
    reg3 = io_in(0x1F4);
    reg4 = io_in(0x1F5);
    // Compare the registers
    if(reg1 == 0x01 && reg2 == 0x01 && reg3 == 0x14 && reg4 == 0xEB){
        return 0; // We have a drive
    }
    return 1; // no drive
}