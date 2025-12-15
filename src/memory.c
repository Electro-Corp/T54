#include "memory.h"

void* malloc(size_t size){
    // Check if we have memory
    if(lastAddr + size > (HEAP_END + heapExtension)){
        // Check versus the physical memory of the system here

        // Extend the heap
        heapExtension += size;
    }
    // If we do, allocate it
    void* ptr = HEAP_START + lastAddr + sizeof(struct chunkHeader);
    lastAddr += size + sizeof(struct chunkHeader);

    // Create a chunk header
    struct chunkHeader tmp = {HEAP_START + lastAddr, sizeof(struct chunkHeader) + HEAP_START + lastAddr + size, 0};
    // Copy the chunk header to right before 
    memcpy(&tmp, HEAP_START + lastAddr, sizeof(struct chunkHeader));
    
    return ptr;
}

void* free(void* ptr){
    // Read the memory chunk

}