/*
    T54
    devices.h - Abstractions for hardware devices
*/
#ifndef DEVICES_H
#define DEVICES_H

#include <stdint.h>

#include "cdrom.h"

struct StorageDevice{
    // Initilize the device
    void (*initDevice)();
    // Read from the device
    void (*readData)(uint16_t location, void* buffer, int count);
};

// 16 Storage Devices
struct StorageDevice storageDevices[16];

// dev_initStorageDevices
// Load all Storage Devices connected to the machine
void dev_initStorageDevices();

// dev_getStorageDeviceWithIndex
// Get the storage device at a specfied index
struct StorageDevice* dev_getStorageDeviceWithIndex(int i);

#endif