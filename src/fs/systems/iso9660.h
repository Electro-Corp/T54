/*
    T54
    iso9660.h - Filesystem implementation for CD-ROM ISO9660 
*/
#ifndef ISO9660_H
#define ISO9660_H

#include "../fs.h"

// iso9660_initFS
// Return a FilesystemImpl
struct FilesystemImpl iso9660_initFS();

// iso9660_openFile
// Open a file oon the system
int iso9660_openFile(const char* name);

// iso9660_readFile
// Read a file into a buffer
void iso9660_readFile(int handle, void* buffer, int n);

#endif