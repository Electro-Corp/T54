#include "cdrom.h"

// cdrom_initDevice
// Return a StorageDevice for devices.h
struct StorageDevice cdrom_initDevice(){
    struct StorageDevice this;
    
    // Copy the device name
    memcpy(&cdromDeviceName, (&this)->name, strlen(cdromDeviceName));
    //
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
    if(io_in(PORT + LBA_HIGH) != 0 || io_in(PORT + LBA_MID) != 0){
        // Not ATA, quit
        return -1;
    }

    // Wait ... (again)
    while(io_in(PORT + COMMAND_REG) & (1 << 0) != 0x00);

    uint16_t identify[256];
    io_insw(PORT, identify, 256);

    // Get the model name
    for (int i = 0; i < 20; i++) {
        cdromDeviceName[i * 2] = identify[27 + i] >> 8;
        cdromDeviceName[i * 2 + 1] = identify[27 + i] & 0xFF;
    }
    cdromDeviceName[40] = '\0';

    // get some other info some time

    return 0; // Success
}

// cdrom_readData
// Read some data from the cd-drive into the buffer
int cdrom_readData(uint32_t lba, uint16_t* buffer, uint32_t sectors){
    return cdrom_readInternal(PORT, 0, lba, sectors, buffer);
}

// cdrom_readInternal
// Internal read with more params 
int cdrom_readInternal(uint16_t port, int slave, uint32_t lba, uint32_t sectors, uint16_t* buffer){
    volatile uint8_t readCommand[12] = {0xA8, 0, (lba >> 0x18) & 0xFF, (lba >> 0x10) & 0xFF, (lba >> 0x08) & 0xFF, (lba >> 0x00) & 0xFF, (sectors >> 0x18) & 0xFF, (sectors >> 0x10) & 0xFF, (sectors >> 0x08) & 0xFF, (sectors >> 0x00) & 0xFF, 0, 0};

    io_out(port + DRIVE_SELECT, 0xA0 & (slave << 4)); // select drive
    cdrom_ataWait(port);
    io_out(port + ERROR, 0x00);
    io_out(port + LBA_MID, 2048 & 0xFF);
    io_out(port + LBA_HIGH, 2048 >> 8);
    io_out(port + COMMAND_REG, 0xA0); // packet 
    cdrom_ataWait(port);

    while(1){
        uint8_t status = io_in(port + COMMAND_REG);
        if((status & 0x01) == 1){
            return -1;
        }
        if(!(status & 0x80) && (status & 0x08)){
            break;
        }
        cdrom_ataWait(port);
    }

    // Send read command
    io_outsw(port, (uint16_t*) readCommand, 6);
    // Read !!
    for(uint32_t i = 0; i < sectors; i++){
        while (1) {
			uint8_t status = io_in(port + COMMAND_REG);
			if (status & 0x01)
				return 1;
			if (!(status & 0x80) && (status & 0x08))
				break;
		}

        // Get size
        int size = io_in(port + LBA_HIGH) << 8 | io_in(port + LBA_MID);
        // Read the data
        io_insw(port, (uint16_t*)((uint8_t*) buffer + i * 0x800), size / 2);
    }

    return 0;
}

// cdrom_ataWait
// Wait 400 ns
void cdrom_ataWait(const uint8_t port){
    io_in(port + CONTROL);
    io_in(port + CONTROL);
    io_in(port + CONTROL);
    io_in(port + CONTROL);
}