/*
    T54
    fs.h - Filesystem abstraction, ./systems contains specfic filesystem implementations
*/
#ifndef FS_H
#define FS_H

struct FilesystemImpl{
    // Name of system
    const char fsName[32];
    // Read-only or no
    int readOnly;
    // Function pointers for specfic 
    // things, such as opening, closing,
    // reading, writing files.

    // Returns a handle... but what handle?
    int (*openFile)(const char* name);
    
    void (*readFile)(/*Handle.. but what handle?*/);
};

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

#endif