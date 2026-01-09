#include "iso9660.h"

// iso9660_initFS
// Return a FilesystemImpl
struct FilesystemImpl iso9660_getFSImpl(){
    struct FilesystemImpl this;

    // FS name
    memcpy("ISO9660", (&this)->fsName, 8);
    // FS is read-only
    this.readOnly = 1;
    // Function pointers
    this.initFilesystem = &iso9660_initFS;
    this.openFile = &iso9660_openFile;
    this.readFile = &iso9660_readFile;

    return this;
}

// iso9660_initFS
void iso9660_initFS(struct StorageDevice* device){
    cdrom = device;
    //
    uint8_t primaryVolumeDescriptor[2048];
    if(!cdrom->readData(16, &primaryVolumeDescriptor, 1)){
        v_terminalWrite("[CD-ROM] Failed to read Primary Volume Descriptor!\n");
    }
}

// iso9660_openFile
// Open a file oon the system
int iso9660_openFile(const char* name){
    return -1;
}

// iso9660_readFile
// Read a file into a buffer
void iso9660_readFile(int handle, void* buffer, int n){

}