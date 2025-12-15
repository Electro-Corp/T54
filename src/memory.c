#include "memory.h"

void* malloc(size_t size){
    // Check if we have memory
    if(lastAddr + size > (HEAP_END + heapExtension)){
        // Check versus the physical memory of the system here

        // Extend the heap
        heapExtension += size;
    }

    // Create a chunk header
    struct chunkHeader tmp = {HEAP_START + lastAddr, sizeof(struct chunkHeader) + HEAP_START + lastAddr + size, 0};
    // Copy the chunk header to right before 
    memcpy(&tmp, HEAP_START + lastAddr, sizeof(tmp));

    // If we do, allocate it
    void* ptr = HEAP_START + lastAddr + sizeof(tmp);
    lastAddr += size + sizeof(tmp);

    return ptr;
}

void* free(void* ptr){
    // Read the memory chunk

}