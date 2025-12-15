/*
    T54
    memory.h - memory allocator and manager
*/
#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

#define HEAP_START 0x1000000 // Start at 16mb
#define HEAP_END 0x4000000 // End at 67 mb

static uint16_t lastAddr;

// malloc
// Allocate some chunk of memory
void* malloc(size_t size);

// free
// Free some chunk of memory
void* free(void* ptr);

#endif