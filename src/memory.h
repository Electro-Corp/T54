/*
    T54
    memory.h - memory allocator and manager
*/
#ifndef MEMORY_H
#define MEMORY_H

static char baseAddr, offset = 0;

// malloc
// Allocate some chunk of memory
void* malloc(int size);

// free
// Free some chunk of memory
void* free(void* ptr);

#endif