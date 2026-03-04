/*  
    T54
    paging.h - Paging 
*/
#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>

#include "std/stdlib.h"

#define FRAME_SIZE 4096 
#define MAX_FRAMES 32768 // 128 MB ram... TODO: read from Multiboot and detect real ram

extern uint32_t kernelEnd; // linker.ld will tell us where our kernel ends, and where we can begin allocation

static uint32_t memoryFrameBitmap[MAX_FRAMES / 8]; // Bitmap (i in byte n tells status of page (n * 8) + i)

typedef struct {
    uint32_t entries[1024];
} Paging_PageTable;

typedef struct {
    uint32_t entries[1024];
} Paging_PageDirectory;

static Paging_PageDirectory kernelDirectory __attribute__((aligned(4096)));
static Paging_PageTable kernelTable __attribute__((aligned(4096)));

// paging_mapFirst4MB
// Map the first 4 megabytes into memory so we can enable paging
void paging_mapFirst4MB();

// paging_allocatePageDirectory
// Allocate a new directory for a process
Paging_PageDirectory* paging_allocatePageDirectory();

// paging_allocatePageTable
// Create a new page table
Paging_PageTable* paging_allocatePageTable();

// paging_mapPage
// Map a physical page to a virtual adderess
void paging_mapPage(Paging_PageDirectory* directory, uint32_t virtualAddress, uint32_t physicalAddress, uint32_t flags);

// paging_loadPageDirectory
// Loads a page directory into memory
void paging_loadPageDirectory(Paging_PageDirectory* pageDir);

// paging_enablePaging
// Enables paging 
void paging_enablePaging();

// paging_allocatePage
// Allocate a page
uint32_t paging_allocatePage();

// paging_getPhysicalAddr
// Get the physical address of a virtual address
void* paging_getPhysicalAddr(Paging_PageDirectory* directory, void *virtualAddr);

#endif