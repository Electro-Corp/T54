#include "devices.h"

// dev_initStorageDevices
// Load all Storage Devices connected to the machine
void dev_initStorageDevices(){
    v_terminalWrite("[DeviceManager] Detect CD-ROM drives...\n");
    if(cdrom_detectDrive() == 0){
        // Print out data
        storageDevices[++storageDeviceCount] = cdrom_initDevice();
        v_terminalWrite("[DeviceManager] CD-ROM drive found: ");
        v_terminalWrite(storageDevices[storageDeviceCount].name);
        v_terminalWrite("\n");
    }else{
        v_terminalWrite("[DeviceManager] CD-ROM not found or not supported.\n");
    }
    v_terminalWrite("[DeviceManager] Detect HDD drives...\n");
    v_terminalWrite("[DeviceManager] No HDD detected.\n");
    // Do something
}

// dev_getStorageDeviceWithIndex
// Get the storage device at a specfied index
struct StorageDevice* dev_getStorageDeviceWithIndex(int i){
    if(i > storageDeviceCount){
        kpanic("Selected device doesn't exist!");
    }
    return &storageDevices[i];
}