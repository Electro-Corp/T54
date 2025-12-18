#include "fs.h"

// fs_init
// Initilize the filesystem
void fs_init(){
    // Dynamically allocate the files buffer cuz
    // we will need to resize at some point
    files = malloc(sizeof(struct File) * 512);
}

// fs_shutdown
// Shutdown the filesystem and sync filesystems
void fs_shutdown(){
    // Do other stuff

    // Clear our files buffer (is this needed? idk... but i can flex my memory stuff)
    free(files);
}

// fs_openFile
// Open a file and get its handle
int fs_openFile(const char* name){
    // temp, in the future call a function
    // within a specfic implementation 
    return -1;
}

// fs_readFile
// Read [n] bytes into a buffer from a file
void fs_readFile(int handle, void* buffer, int n){

}

// fs_writeFile
// Write [n] bytes into a file from buffer 
void fs_writeFile(int handle, void* buffer, int n){

}

// fs_closeFile
// Close a file and free its handle
void fs_closeFile(int handle){

}

// fs_generateFileHandle
// Get HANDLE for a new file
int fs_generateFileHandle(const char* fileName){
    struct File tmp = fs_generateFileStruct(fileName);
    // add to files here

    // return the handle
    return tmp.handle;
}

// fs_generateFileStruct
// Generate a new file
struct File fs_generateFileStruct(const char* fileName){
    struct File tmp = {-1, fileName};
    return tmp;
}