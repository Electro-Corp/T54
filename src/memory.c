#include "memory.h"

void* malloc(size_t size){
    uint16_t startMemory = HEAP_START + lastAddr;
    // First, check if we have a freed chunk we could
    // repurpose
    int usingPreviouslyAlloc = -1;
    for(int i = 0; i < lastFreeChunk; i++){
        if(freeChunks[i].free == 1 && freeChunks[i].end - freeChunks[i].start >= size){
            usingPreviouslyAlloc = i;
            freeChunks[i].free = 0;
            startMemory = freeChunks[i].start;
            // Split this chunk of memory, should we need it
            if(freeChunks[i].end - freeChunks[i].start > size){
                // bigger than we need
                struct chunkHeader split = {freeChunks[i].end, freeChunks[i].end + (freeChunks[i].end - freeChunks[i].start - size), 1, lastFreeChunk++};
                freeChunks[lastFreeChunk] = split;
                // Resize the original
                freeChunks[i].end = startMemory + sizeof(freeChunks[i]) + size;
            }
            break;
        }
    }

    // Check if we have memory
    if(lastAddr + size > (HEAP_END + heapExtension) && usingPreviouslyAlloc == -1){
        // Check versus the physical memory of the system here

        // Extend the heap
        heapExtension += size; // do something with this value in the future
    }

    if(usingPreviouslyAlloc == -1){
        // Create a chunk header
        struct chunkHeader tmp = {startMemory, sizeof(struct chunkHeader) + startMemory + size, 0, -1};
        // Copy the chunk header to right before 
        memcpy(&tmp, startMemory, sizeof(tmp));
    }else{
        // Copy our current chunk
        memcpy(&freeChunks[usingPreviouslyAlloc], startMemory, sizeof(struct chunkHeader));
    }
    // If we do, allocate it
    void* ptr = startMemory + sizeof(struct chunkHeader);
    lastAddr += size + sizeof(struct chunkHeader);

    return ptr;
}

void* free(void* ptr){
    // Read the memory chunk at that location
    void* chunkPtr = ptr - sizeof(struct chunkHeader);
    struct chunkHeader h;
    memcpy(chunkPtr, &h, sizeof(struct chunkHeader));

    // Have we already freed this one before?
    if(h.index != -1){
        h.free = 1;
        freeChunks[h.index] = h;
    }else{
        // Store it and remember it
        h.free = 1;
        h.index = lastFreeChunk++;
        freeChunks[lastFreeChunk] = h;
    }
}