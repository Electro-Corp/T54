#include "paging.h"

// paging_mapFirst4MB
// Map the first 4 megabytes into memory so we can enable paging
void paging_mapFirst4MB(){
    for(int i = 0; i < 1024; i++){
        kernelPageProcess.table->entries[i] = ((i * 0x1000) | 0x3); // Get the physical address and then set 
    }

    kernelPageProcess.directory.entries[0] = ((uint32_t) kernelPageProcess.table) | 3;

    paging_loadPageDirectory(&kernelPageProcess);
}

// paging_allocatePagingProcess
// Create a new Paging_Process
Paging_Process* paging_allocatePagingProcess(){
    Paging_Process process;
    process.directory = paging_allocatePageDirectory();
    process.table = paging_allocatePageTable();

    // heap
    process.lastAddr = 0;
    process.heapExtension = 0;
    process.lastFreeChunk = 0;

    return &process;
}

// paging_allocatePageDirectory
// Allocate a new directory for a process
Paging_PageDirectory paging_allocatePageDirectory(){
    Paging_PageDirectory directory __attribute__((aligned(4096)));

    return directory;
}

// paging_allocatePageTable
// Create a new page table
Paging_PageTable* paging_allocatePageTable(){
    Paging_PageTable* table = (Paging_PageTable*)paging_allocatePage();
    for(int i = 0; i < 1024; i++){
        table->entries[i] = 0;
    }
    return table;
}

// paging_mapPage
// Map a physical page to a virtual adderess
void paging_mapPage(Paging_Process* process, uint32_t virtualAddress, uint32_t physicalAddress, uint32_t flags){
    // Page align the addresses
    uint32_t pageDirectoryIdx = (virtualAddress >> 22) & 0x3FF;
    uint32_t pageTableIdx = (virtualAddress >> 12) & 0x3FF;
    
    Paging_PageTable* pageTable;

    if(!(process->directory.entries[pageDirectoryIdx] & 1)){
        pageTable = paging_allocatePageTable();
        process->directory.entries[pageDirectoryIdx] = ((uint32_t) pageTable) | flags | 0x01;
    }else{
        pageTable = (Paging_PageTable*)(process->directory.entries[pageDirectoryIdx] & 0xFFFFF000);
    }

    pageTable->entries[pageTableIdx] = physicalAddress | (flags & 0xFFF) | 0x01; // we exist 
}

// paging_loadPageDirectory
// Loads a page directory into memory
void paging_loadPageDirectory(Paging_Process* proc){
    Paging_PageDirectory* directory = &(proc->directory);
    asm volatile("mov %0, %%cr3" :: "r"(directory)); // page directory into cr3
}

// paging_enablePaging
// Enables paging 
void paging_enablePaging(){
    uint32_t cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000;
    asm volatile("mov %0, %%cr0" :: "r"(cr0)); 
}

// paging_allocatePage
// Allocate a page
uint32_t paging_allocatePage(){
    for(int i = 0; i < MAX_FRAMES; i++){
        uint32_t id = i / 32, bit = i % 32;
        if(!(memoryFrameBitmap[id] & (1 << bit))){ // This page is free
            memoryFrameBitmap[i] |= (1 << bit);
            return i * 0x1000;
        }
    }
    return 0; // oh no
}

// paging_getPhysicalAddr
// Get the physical address of a virtual address
void* paging_getPhysicalAddr(Paging_Process* process, void *virtualAddr){
    // Page align the addresses
    uint32_t pageDirectoryIdx = ((unsigned long)virtualAddr >> 22) & 0x3FF;
    uint32_t pageTableIdx = ((unsigned long)virtualAddr >> 12) & 0x3FF;

    // Is the Page table a thing
    if((process->directory.entries[pageDirectoryIdx] & 1)){
        return (void*)(process->directory.entries[pageDirectoryIdx] & ~0xFF) + ((unsigned long)virtualAddr & 0xFF);
    }

    return 0;
}