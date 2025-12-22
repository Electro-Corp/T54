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
// Get drive data
int cdrom_detectDrive(){
    // Select master
    io_out(PORT + DRIVE_SELECT, 0xA0);
    // Set stuff to 0
    io_out(PORT + SECTOR_COUNT, 0);
    io_out(PORT + LBA_LOW, 0);
    io_out(PORT + LBA_MID, 0);
    io_out(PORT + LBA_HIGH, 0);
    // Send identify
    io_out(PORT + COMMAND_REG, INDENTIFY);
    // Read status
    unsigned char exists = io_in(PORT + COMMAND_REG);
    if(exists == 0x00) return -1;

    // Block until we can actually get data
    while(io_in(PORT + COMMAND_REG) & (1 << 7) != 0x00);

    // Check if we're actually ATA
    // if(io_in(PORT + LBA_HIGH) != 0 || io_in(PORT + LBA_MID) != 0){
    //     // Not ATA, quit
    //     return -1;
    // }

    // Wait ... (again)
    while(io_in(PORT + COMMAND_REG) & (1 << 0) != 0x00);

    uint16_t idnetify[256];
    io_insw(PORT, idnetify, 256);

    char model[41];
    for (int i = 0; i < 20; i++) {
        model[i * 2] = identify[27 + i] >> 8;
        model[i * 2 + 1] = identify[27 + i] & 0xFF;
    }
    model[40] = '\0';
    v_terminalWrite(model);

    return 0;
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

