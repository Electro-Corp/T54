/*
    T54
    fs.h - Filesystem abstraction, ./systems contains specfic filesystem implementations
*/
#ifndef FS_H
#define FS_H

#include "../panic.h"
#include "../memory.h"
#include "../drivers/devices.h"

struct FilesystemImpl{
    // Name of system
    char fsName[32];
    // Read-only or no
    int readOnly;
    // Function pointers for specfic 
    // things, such as opening, closing,
    // reading, writing files.

    // Initilize the filesystem
    void (*initFilesystem)(struct StorageDevice* device);
    // Close the filesystem
    void (*closeFilesystem)(void);
    // Returns a handle. 
    int (*openFile)(const char* name);
    // Reads a file
    int (*readFile)(int handle, void* buffer, int n);
    // Writes a file
    void (*writeFile)(int handle, void* buffer, int n);
};

// File
struct File{
    int handle, internalHandle, used;
    const char fileName[256];
};

// Errors
enum FS_Errors{
    TRIED_TO_OPEN_DIRECTORY = -1,
    FILE_NOT_FOUND = -2,
    INVALID_FS_HANDLE = -3,
    INVALID_IMPL_HANDLE = -4
};

// File buffer
static struct File* files;
static int fileCount;

// Root device
static struct StorageDevice* rootDevice;
// Root FS
static struct FilesystemImpl rootFS;

// fs_init
// Initilize the filesystem
void fs_init(struct StorageDevice* rootDeviceIn);

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
int fs_readFile(int handle, void* buffer, int n);

// fs_writeFile
// Write [n] bytes into a file from buffer 
void fs_writeFile(int handle, void* buffer, int n);

// fs_closeFile
// Close a file and free its handle
int fs_closeFile(int handle);

// These are functions that implementations can call

// fs_generateFileHandle
// Get HANDLE for a new file
int fs_generateFileHandle(const char* fileName, int implId);

// fs_generateFileHandle
// Generate a new file, and store it in our data
struct File fs_generateFileStruct(const char* fileName, int implId);

// fs_findNextHandle
// Get next free handle
int fs_findNextHandle();

#endif