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
    this.closeFilesystem = &iso9660_closeFS;

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

    // Init directories
    entires = malloc(sizeof(struct iso9660DirectoryEntry) * 256);

    // Root directory extent
    uint32_t rootLBA = iso9660_littleEndianTo32(iso9660_getFour(&primaryVolumeDescriptor, FIRST_DIRECTORY_ENTRY_OFFSET + 10));
    // Start parsing
    iso9660_parseDirectory(rootLBA, "/");
}

// iso9660_parseDirectory
// Parse a directory record and add it to our list
void iso9660_parseDirectory(uint32_t lba, char* directory){

}

// iso9660_openFile
// Open a file oon the system
int iso9660_openFile(const char* name){
    // Search the path table
    
    return -1;
}

// iso9660_readFile
// Read a file into a buffer
void iso9660_readFile(int handle, void* buffer, int n){

}

// iso9660_closeFS
// Close the filesystem
void iso9660_closeFS(){
    free(entires);
}

// iso9660_getFour
// Get next four from an array
uint8_t* iso9660_getFour(uint8_t* buffer, int start){
    uint8_t tmp[4];
    for(int i = start; i < 4; i++){
        tmp[i - start] = buffer[i];
    }
    return tmp;
}

// iso9660_littleEndianTo32
// Convert four uint8_t to uint_32_t
uint32_t iso9660_littleEndianTo32(uint8_t* bytes) {
	uint32_t value = 0;
	for (int i = 0; i < 4; i++) {
		value |= bytes[i] << (i * 8);
	}
	return value;
}