/*
    T54
    memory.h - memory allocator and manager
*/
#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

#include "std/stdlib.h"

#include "paging.h"

#define HEAP_START 0x1000000 // Start at 16mb
#define HEAP_END 0x4000000 // End at 67 mb, extendable when needed
#define INITIAL_FREECHUNK_MAX 256

static uint16_t lastAddr = 0;
static uint16_t heapExtension = 0;

struct chunkHeader{
    uint16_t start, end;
    int free, index;
} __attribute__((packed));

static struct chunkHeader freeChunks[INITIAL_FREECHUNK_MAX]; // need a way to increase his when needed
                                                            // i have an idea, but i dunno how "proper" it is
static int lastFreeChunk = 0;

// kmalloc
// Allocate some chunk of memory
void* kmalloc(size_t size);

// kmalloc_loc
// Allocate memory at a specfic location
void* kmalloc_loc(size_t size, uint32_t location, int prevAllocation);

// free
// Free some chunk of memory
void* free(void* ptr);

// memory_GetAllocatedChunks
// Get current amount of allocated chunks
int memory_GetAllocatedChunks();

#endif