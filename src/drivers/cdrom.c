#include "cdrom.h"

// cdrom_initDevice
// Return a StorageDevice for devices.h
struct StorageDevice cdrom_initDevice(){
    struct StorageDevice this;
    
    this.type = CD_ROM;
    this.readData = &cdrom_readData;

    return this;
}

// cdrom_detectDrive
// Is there a drive present
// This doesn't work on qemu, untested on real hardware
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
    if(reg1 == 0x01 && reg2 == 0x01){
        // Check if packet device or not
        if(reg3 == 0x14 && reg4 == 0xEB){
            // Packet
        }else if(reg3 == 0x00 && reg4 == 0x00){
            // Nah
        }else{
            return 1; // no drive
        }
        return 0;
    }
    return 1; // no drive
}

// cdrom_readData
// Read some data from the cd-drive into the buffer
void cdrom_readData(uint32_t lba, uint16_t* buffer, uint32_t sectors){
    cdrom_readInternal(PORT, 0, lba, sectors, buffer);
}

// cdrom_readInternal
// Internal read with more params
void cdrom_readInternal(uint16_t port, int slave, uint32_t lba, uint32_t sectors, uint16_t* buffer){

}

