#include "memory.h"

void* malloc(int size){
    if(!baseAddr){
        baseAddr = ' ';
    }

    void* location = &baseAddr;
    offset += size;
    return location;
}

void* free(void* ptr){
    
}