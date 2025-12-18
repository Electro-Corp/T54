/*
    T54
    devices.h - Abstractions for hardware devices
*/
#ifndef DEVICES_H
#define DEVICES_H

#include <stdint.h>

#include "cdrom.h"

//
// Device declerations
//

enum StorageType{
    HARD_DRIVE = 0,
    CD_ROM = 1,
    USB = 2
};

struct StorageDevice{
    enum StorageType type;
    // Initilize the device
    void (*initDevice)();
    // Read from the device
    void (*readData)(uint32_t location, uint16_t* buffer, uint32_t count);
};

//
// Storage
//

// 16 Storage Devices
static struct StorageDevice storageDevices[16]; 
static int storageDeviceCount;

// dev_initStorageDevices
// Load all Storage Devices connected to the machine
void dev_initStorageDevices();

// dev_getStorageDeviceWithIndex
// Get the storage device at a specfied index
struct StorageDevice* dev_getStorageDeviceWithIndex(int i);

#endif