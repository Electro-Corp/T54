#include "devices.h"

// dev_initStorageDevices
// Load all Storage Devices connected to the machine
void dev_initStorageDevices(){
    v_terminalWrite("[DeviceManager] Detect CD-ROM drives...\n");
    if(cdrom_detectDrive() == 0){
        // Print out data
        v_terminalWrite("[DeviceManager] One CD-ROM drive found.\n" /* insert data here later*/);
        storageDevices[storageDeviceCount++] = cdrom_initDevice();
    }else{
        v_terminalWrite("[DeviceManager] CD-ROM not found or not supported.\n");
    }
    v_terminalWrite("[DeviceManager] Detect HDD drives...\n");
    // Do something
}

// dev_getStorageDeviceWithIndex
// Get the storage device at a specfied index
struct StorageDevice* dev_getStorageDeviceWithIndex(int i){
    return &storageDevices[i];
}