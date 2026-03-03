/*
    T54
    devices.h - Abstractions for hardware devices
*/
#ifndef DEVICES_H
#define DEVICES_H

#include <stdint.h>

#include "../video.h"
#include "../panic.h"
// Devices
#include "cdrom.h"

//
// Device declerations
//

enum StorageType{
    HARD_DRIVE = 0,
    CD_ROM = 1,
    USB = 2
};

// Generic Storage Device
struct StorageDevice{
    enum StorageType type;
    // Name
    char name[64];
    // Initilize the device
    void (*initDevice)();
    // Read from the device
    int (*readData)(uint32_t location, uint16_t* buffer, uint32_t count);
};

//
// Storage
//

// 16 Storage Devices, its enough for everybody!
static struct StorageDevice storageDevices[16];
static int storageDeviceCount = -1;

// dev_initStorageDevices
// Load all Storage Devices connected to the machine
void dev_initStorageDevices();

// dev_getStorageDeviceWithIndex
// Get the storage device at a specfied index
struct StorageDevice* dev_getStorageDeviceWithIndex(int i);

#endif