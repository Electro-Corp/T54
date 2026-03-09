/*  
    T54
    paging.h - Paging 
*/
#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>

#include "std/stdlib.h"

#define KERNEL_BASE 0xC0000000
#define FRAME_SIZE 4096 
#define MAX_FRAMES 4096  // TODO: read from Multiboot and detect real ram
#define HEAP_START 0x0000000 // Start at 0mb
#define HEAP_END 0x1000000  // End at 16 mb, extendable when needed
#define INITIAL_FREECHUNK_MAX 256

extern uint32_t kernelEnd; // linker.ld will tell us where our kernel ends, and where we can begin allocation
static uint32_t memoryFrameBitmap[MAX_FRAMES / 8]; // Bitmap (i in byte n tells status of page (n * 8) + i)

typedef struct {
    uint32_t entries[1024];
} Paging_PageTable;

typedef struct {
    uint32_t entries[1024];
} Paging_PageDirectory;

struct chunkHeader{
    uint16_t start, end;
    int free, index;
} __attribute__((packed));

typedef struct {
    // Paging
    Paging_PageDirectory* directory __attribute__((aligned(4096)));
    Paging_PageTable* tables[1024] __attribute__((aligned(4096)));
    int tableCount;

    // Heap allocation
    uint32_t lastAddr; // Last allocated address
    uint32_t heapExtension; // Exend the heap?
    struct chunkHeader freeChunks[INITIAL_FREECHUNK_MAX]; // Current chunks 
    int lastFreeChunk; // Last free chunk we found
} Paging_Process;

static Paging_PageDirectory kernelPageDirectory __attribute__((aligned(4096)));
static Paging_PageTable kernelFirstTable __attribute__((aligned(4096)));

// Page directory and table for the kernel
static Paging_Process kernelPageProcess __attribute__((aligned(4096)));

// Last directory in cr3
static Paging_Process* currentlyLoadedProcess __attribute__((aligned(4096)));

// paging_mapFirst4MB
// Map the first 4 megabytes into memory so we can enable paging
void paging_mapFirst4MB();

// paging_allocatePagingProcess
// Create a new Paging_Process
Paging_Process* paging_allocatePagingProcess();

// paging_allocatePageDirectory
// Allocate a new directory
Paging_PageDirectory* paging_allocatePageDirectory();

// paging_allocatePageTable
// Create a new page table
Paging_PageTable* paging_allocatePageTable();

// paging_allocatePageTableAtAddr
// Create a new page table at an address
Paging_PageTable* paging_allocatePageTableAtAddr(void* location);

// paging_mapPage
// Map a physical page to a virtual adderess
void paging_mapPage(Paging_Process* proc, uint32_t virtualAddress, uint32_t physicalAddress, uint32_t flags);

// paging_loadPageDirectory
// Loads a page directory into memory
void paging_loadPageDirectory(Paging_Process* proc);

// paging_enablePaging
// Enables paging 
void paging_enablePaging();

// paging_allocatePage
// Allocate a page
uint32_t paging_allocatePage();

// paging_getPhysicalAddr
// Get the physical address of a virtual address
void* paging_getPhysicalAddr(Paging_Process* proc, void* virtualAddr);

// paging_getCurrentlyLoadedProcess
// Get the current loaded process in cr3
Paging_Process* paging_getCurrentlyLoadedProcess();

#endif