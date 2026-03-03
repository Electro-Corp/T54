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
// Cache directories
void iso9660_initFS(struct StorageDevice* device){
    cdrom = device;
    //
    uint8_t primaryVolumeDescriptor[2048];
    if(cdrom->readData(16, (uint16_t*)primaryVolumeDescriptor, 1) != 0){
        v_terminalWrite("[CD-ROM] Failed to read Primary Volume Descriptor!\n");
    }

    // Root directory extent
    uint32_t rootLBA = iso9660_littleEndianTo32(primaryVolumeDescriptor + FIRST_DIRECTORY_ENTRY_OFFSET + 2);
    // Start parsing
    v_terminalWrite("[ISO9660] Caching directories...");
    // Init directories
    entries = malloc(sizeof(struct iso9660DirectoryEntry) * 256);
    // Cache
    iso9660_parseDirectory(rootLBA, "/");
    v_terminalWrite("done.\n");
}

// iso9660_parseDirectory
// Parse a directory record and add it to our list
void iso9660_parseDirectory(uint32_t dirLba, char* directory){
    // Load the sector into memory
    uint8_t directorySector[2048];
    if(cdrom->readData(dirLba, (uint16_t*)directorySector, 1) != 0){
        v_terminalWrite("[CD-ROM] Failed to read sector!\n");
    }
    int currentPos = 0, safety = 0;
    for(safety = 0; safety < 256; safety++){
        // Begin retriving data
        struct iso9660DirectoryEntry entry;
        // Basic info
        uint8_t flags = directorySector[currentPos + 25];
        uint8_t idSize = directorySector[currentPos + 32];

        entry.isDirectory = (flags >> 1) & 1;

        char tempName[64] = {0};

        if(!entry.isDirectory) idSize -= 2; // Remove ";n" from the end

        memcpy(directorySector + currentPos + 33, tempName, idSize);

        tempName[idSize] = '\0';

        // "." directory
        if(idSize < 1){
            tempName[0] = '.';
            tempName[1] = '\0';
        }

        entry.location = iso9660_littleEndianTo32(directorySector + currentPos + 2);
        entry.size = iso9660_littleEndianTo32(directorySector + currentPos + 10);

        char fullPath[256] = {0};
        if(idSize > 1){
            strcat(fullPath, directory);
            strcat(fullPath, tempName);
            if(entry.isDirectory) strcat(fullPath, "/");

            strcpy(fullPath, entry.fileName);

            v_terminalWrite(entry.fileName);
            v_terminalWrite("\n");

            entries[entryCount++] = entry;
        }

        if(entry.isDirectory && idSize > 1){
            iso9660_parseDirectory(entry.location, fullPath);
        }

        currentPos += directorySector[currentPos];
        if(directorySector[currentPos] == 0) break;
    }
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
    free(entries);
}

// iso9660_littleEndianTo32
// Convert four uint8_t to uint_32_t
uint32_t iso9660_littleEndianTo32(uint8_t* bytes) {
	uint32_t value = 0;
	for (int i = 0; i < 4; i++) {
		value |= (uint32_t) bytes[i] << (i * 8);
	}
	return value;
}