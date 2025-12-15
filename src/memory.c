#include "memory.h"

void* malloc(size_t size){
    // Check if we have memory
    if(lastAddr + size > HEAP_END){
        // Throw an error
        return;
    }
    // If we do, allocate it
    void* ptr = HEAP_START + lastAddr;
    lastAddr += size;
    return ptr;
}

void* free(void* ptr){
    
}