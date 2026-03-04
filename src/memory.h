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

// kmalloc
// Allocate some chunk of memory (assumes kernel page)
void* kmalloc(size_t size);

// kmalloc_loc
// Allocate memory at a specfic location (assumes kernel page)
void* kmalloc_loc(size_t size, uint32_t location, int prevAllocation);

// kmalloc_directory
// Allocate memory at a location with a specfic Paging_Process
void* kmalloc_directory(Paging_Process* proc, size_t size, uint32_t location, int prevAllocation);

// free
// Free some chunk of memory
void* free(void* ptr);

// free_directory
// Free memory at a location with a specfic Paging_Process
void* free_directory(Paging_Process* proc, void* ptr);

// memory_GetAllocatedChunks
// Get current amount of allocated chunks
int memory_GetAllocatedChunks();

#endif