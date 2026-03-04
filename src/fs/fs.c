#include "fs.h"

// Include filesystems
#include "systems/iso9660.h"

// fs_init
// Initilize the filesystem
void fs_init(struct StorageDevice* rootDeviceIn){
    // Dynamically allocate the files buffer cuz
    // we will need to resize at some point
    files = kmalloc(sizeof(struct File) * 512);
    // Root FS
    rootDevice = rootDeviceIn;

    switch(rootDevice->type){
        case CD_ROM:
            // ISO9660
            rootFS = iso9660_getFSImpl();
            break;
        default:
            // Nothing...
            kpanic("Failed to mount root FS!");
            break;
    }

    v_terminalWrite("[Filesystem] Initlizing ");
    v_terminalWrite(rootFS.fsName);
    v_terminalWrite(" as the root filesystem...\n");

    rootFS.initFilesystem(rootDevice);
}

// fs_openFile
// Open a file and get its handle
int fs_openFile(const char* name){
    // Call FS impl
    int fileID = rootFS.openFile(name);
    if(fileID < 0){
        return fileID; // It's an error 
    }
    // Generate an id
    int id = fs_generateFileHandle(name, fileID);
    return id;
}

// fs_readFile
// Read [n] bytes into a buffer from a file
int fs_readFile(int handle, void* buffer, int n){
    // Get file
    if(handle > fileCount || files[handle].used == 0 || handle < 0) return INVALID_FS_HANDLE; // Handle is invalid
    
    int implHandle = files[handle].internalHandle;
    int error = rootFS.readFile(implHandle, buffer, n);

    return error;
}

// fs_writeFile
// Write [n] bytes into a file from buffer 
void fs_writeFile(int handle, void* buffer, int n){
    
}

// fs_closeFile
// Close a file and free its handle
int fs_closeFile(int handle){
    // Get file
    if(handle > fileCount || files[handle].used == 0 || handle < 0) return INVALID_FS_HANDLE; // Handle is invalid
    // Set used to nah
    files[handle].used = 0;

    return 0;
}

// fs_shutdown
// Shutdown the filesystem and sync filesystems
void fs_shutdown(){
    // Do other stuff
    rootFS.closeFilesystem();

    // Clear our files buffer 
    // (is this needed since the OS is exiting at this point? idk... but i can flex my memory stuff)
    free(files);
}

// fs_generateFileHandle
// Get HANDLE for a new file
int fs_generateFileHandle(const char* fileName, int implId){
    struct File tmp = fs_generateFileStruct(fileName, implId);
    // add to files here
    if(tmp.handle < fileCount){
        memcpy(&tmp, files + tmp.handle, sizeof(tmp));
    }else{
        memcpy(&tmp, files + fileCount, sizeof(tmp));
    }
    // return the handle
    return tmp.handle;
}

// fs_generateFileStruct
// Generate a new file
struct File fs_generateFileStruct(const char* fileName, int implId){
    struct File tmp;
    strcpy(fileName, tmp.fileName);
    tmp.handle = fs_findNextHandle();
    tmp.internalHandle = implId;
    tmp.used = 1;
    return tmp;
}

// fs_findNextHandle
// Get next free handle
int fs_findNextHandle(){
    for(int i = 0; i < fileCount; i++){
        if(files[i].used == 0) return files[i].handle;
    }
    return fileCount;
}