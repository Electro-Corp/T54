#include "devices.h"

// dev_initStorageDevices
// Load all Storage Devices connected to the machine
void dev_initStorageDevices(){

}

// dev_getStorageDeviceWithIndex
// Get the storage device at a specfied index
struct StorageDevice* dev_getStorageDeviceWithIndex(int i){
    return &storageDevices[i];
}