/*
    T54
    iso9660.h - Filesystem implementation for CD-ROM ISO9660 
*/
#ifndef ISO9660_H
#define ISO9660_H

#include "../fs.h"

// Location of initial Directory Entry
#define FIRST_DIRECTORY_ENTRY_OFFSET 156

struct iso9660DirectoryEntry{
    char fileName[64];
    uint32_t location, size;
    int isDirectory;
};

// Device to read from
static struct StorageDevice* cdrom;

// Cache of directories in disk
static struct iso9660DirectoryEntry* entires;
static int entryCount = 0;

// iso9660_getFSImpl
// Return a FilesystemImpl
struct FilesystemImpl iso9660_getFSImpl();

// iso9660_initFS
// Initilize the filesystem
void iso9660_initFS(struct StorageDevice* device);

// iso9660_parseDirectory
// Parse a directory record and add it to our list
void iso9660_parseDirectory(uint32_t lba, char* directory);

// iso9660_openFile
// Open a file oon the system
int iso9660_openFile(const char* name);

// iso9660_readFile
// Read a file into a buffer
void iso9660_readFile(int handle, void* buffer, int n);

// iso9660_closeFS
// Close the filesystem
void iso9660_closeFS();

// iso9660_getFour
// Get next four from an array
uint8_t* iso9660_getFour(uint8_t* buffer, int start);

// iso9660_littleEndianTo32
// Convert four uint8_t to uint_32_t
uint32_t iso9660_littleEndianTo32(uint8_t* bytes);

#endif