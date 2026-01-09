/*
    T54/drivers
    cdrom.h - ATAPI cdrom driver
*/
#ifndef CDROM_H
#define CDROM_H

#include <stddef.h>

#include "../io.h"
#include "../std/stdlib.h"
#include "devices.h"

// Base
#define PORT 0x1F0
// Offset registers
#define ERROR 1
#define SECTOR_COUNT 2
#define LBA_LOW 3
#define LBA_MID 4
#define LBA_HIGH 5
#define DRIVE_SELECT 6
#define COMMAND_REG 7
// Control reg
#define CONTROL 0x206

#define INDENTIFY 0xA1
#define READ 0xA8
#define WRITE 0xAA

static char cdromDeviceName[64];

// cdrom_initDevice
// Return a StorageDevice for devices.h
struct StorageDevice cdrom_initDevice();

// cdrom_detectDrive
// Is there a drive present
int cdrom_detectDrive();

// cdrom_readData
// Read some data from the cd-drive into the buffer
void cdrom_readData(uint32_t lba, uint16_t* buffer, uint32_t sectors);


// internal func   
//   func  internal

// cdrom_readInternal
// Internal read with more params
void cdrom_readInternal(uint16_t port, int slave, uint32_t lba, uint32_t sectors, uint16_t* buffer);

// cdrom_ataWait
// Wait 400 ns
void cdrom_ataWait(const uint8_t port);

#endif