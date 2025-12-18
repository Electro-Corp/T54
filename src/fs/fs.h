/*
    T54
    fs.h - Filesystem abstraction, ./systems contains specfic filesystem implementations
*/
#ifndef FS_H
#define FS_H

#include "../memory.h"
#include "../drivers/devices.h"

struct FilesystemImpl{
    // Name of system
    const char fsName[32];
    // Read-only or no
    int readOnly;
    // Function pointers for specfic 
    // things, such as opening, closing,
    // reading, writing files.

    // Returns a handle. 
    int (*openFile)(const char* name);
    // Reads a file
    void (*readFile)(int handle, void* buffer, int n);
    // Writes a file
    void (*writeFile)(int handle, void* buffer, int n);
};

// File
struct File{
    int handle; // Very important
    const char* fileName;
};

// File buffer
static struct File* files;

// fs_init
// Initilize the filesystem
void fs_init();

// fs_shutdown
// Shutdown the filesystem and sync filesystems
void fs_shutdown();

// These are functions that the kernel can call,
// with no need to worry about the backend filesystem

// fs_openFile
// Open a file and get its handle
int fs_openFile(const char* name);

// fs_readFile
// Read [n] bytes into a buffer from a file
void fs_readFile(int handle, void* buffer, int n);

// fs_writeFile
// Write [n] bytes into a file from buffer 
void fs_writeFile(int handle, void* buffer, int n);

// fs_closeFile
// Close a file and free its handle
void fs_closeFile(int handle);

// These are functions that implementations can call

// fs_generateFileHandle
// Get HANDLE for a new file
int fs_generateFileHandle(const char* fileName);

// fs_generateFileHandle
// Generate a new file, and store it in our data
struct File fs_generateFileStruct(const char* fileName);

#endif