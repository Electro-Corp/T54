#include "memory.h"

// kmalloc
// Allocate some chunk of memory 
void* kmalloc(size_t size){
    Paging_Process* proc = paging_getCurrentlyLoadedProcess();

    uint16_t startMemory = HEAP_START + proc->lastAddr;
    // First, check if we have a freed chunk we could
    // repurpose
    int usingPreviouslyAlloc = -1;
    for(int i = 0; i < proc->lastFreeChunk; i++){
        if(proc->freeChunks[i].free == 1 && proc->freeChunks[i].end - proc->freeChunks[i].start >= size){
            usingPreviouslyAlloc = i;
            proc->freeChunks[i].free = 0;
            startMemory = proc->freeChunks[i].start;
            // Split this chunk of memory, should we need it
            if(proc->freeChunks[i].end - proc->freeChunks[i].start > size){
                // bigger than we need
                struct chunkHeader split = {proc->freeChunks[i].end, proc->freeChunks[i].end + (proc->freeChunks[i].end - proc->freeChunks[i].start - size), 1, proc->lastFreeChunk++};
                proc->freeChunks[proc->lastFreeChunk] = split;
                // Resize the original
                proc->freeChunks[i].end = startMemory + sizeof(proc->freeChunks[i]) + size;
            }
            break;
        }
    }

    return kmalloc_loc(size, startMemory, usingPreviouslyAlloc);
}

// kmalloc_loc
// Allocate memory at a specfic location (assumes kernel page process)
void* kmalloc_loc(size_t size, uint32_t location, int prevAllocation){
   return kmalloc_directory(paging_getCurrentlyLoadedProcess(), size, location, prevAllocation); 
}  


// kmalloc_directory
// Allocate memory at a location with a specfic page directory
void* kmalloc_directory(Paging_Process* proc, size_t size, uint32_t location, int prevAllocation){   
    paging_mapPage(proc, location, paging_allocatePage(), 0x3);
    // Convert location
    void* realLocation = paging_getPhysicalAddr(proc, &location);
    // Check if we have memory
    if(proc->lastAddr + size > (HEAP_END + proc->heapExtension) && prevAllocation == -1){
        // Check versus the physical memory of the system here

        // Extend the heap
        proc->heapExtension += size; // do something with this value in the future
    }

    if(prevAllocation == -1){
        // Create a chunk header
        struct chunkHeader tmp = {(unsigned long)realLocation, sizeof(struct chunkHeader) + (unsigned long)realLocation + size, 0, -1};
        // Copy the chunk header to right before 
        memcpy(&tmp, &location, sizeof(tmp));
    }else{
        // Copy our current chunk
        memcpy(&(proc->freeChunks)[prevAllocation], realLocation, sizeof(struct chunkHeader));
    }
    // If we do, allocate it
    void* ptr = realLocation + sizeof(struct chunkHeader);
    proc->lastAddr += size + sizeof(struct chunkHeader);

    return ptr;
}

// free
// Free some chunk of memory
void* free(void* ptr){
    free_directory(paging_getCurrentlyLoadedProcess(), ptr);
}

// free_directory
// Free memory at a location with a specfic page directory 
void* free_directory(Paging_Process* proc, void* ptr){
    void* realLocation = paging_getPhysicalAddr(proc, ptr);
    // Read the memory chunk at that location
    void* chunkPtr = realLocation - sizeof(struct chunkHeader);
    struct chunkHeader h;
    memcpy(chunkPtr, &h, sizeof(struct chunkHeader));

    // Have we already freed this one before?
    if(h.index != -1){
        h.free = 1;
        proc->freeChunks[h.index] = h;
    }else{
        // Store it and remember it
        h.free = 1;
        h.index = proc->lastFreeChunk++;
        proc->freeChunks[proc->lastFreeChunk] = h;
    }
}

// memory_GetAllocatedChunks
// Get current amount of allocated chunks
int memory_GetAllocatedChunks(){
   return 0;
}