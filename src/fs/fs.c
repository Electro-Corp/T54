#include "fs.h"

// fs_init
// Initilize the filesystem
void fs_init(){

}

// fs_openFile
// Open a file and get its handle
int fs_openFile(const char* name){
    // CHANGE THIS THIS IS NOT RIGHT 
    return fs_generateFileHandle(name).handle;
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
// Generate a new file
struct File fs_generateFileHandle(const char* fileName){
    struct File tmp = {-1, fileName};
    return tmp;
}