/*
    T54/drivers
    cdrom.h - ATAPI cdrom driver
*/
#ifndef CDROM_H
#define CDROM_H

#include <stddef.h>

#include "../io.h"
#include "devices.h"

#define PORT 0x1F0

// cdrom_initDevice
// Return a StorageDevice for devices.h
struct StorageDevice cdrom_initDevice();

// cdrom_detectDrive
// Is there a drive present
int cdrom_detectDrive();

// cdrom_readData
// Read some data from the cd-drive into the buffer
void cdrom_readData(uint32_t lba, uint16_t* buffer, uint32_t sectors);


// internal
//         internal

// cdrom_readInternal
// Internal read with more params
void cdrom_readInternal(uint16_t port, int slave, uint32_t lba, uint32_t sectors, uint16_t* buffer);

#endif