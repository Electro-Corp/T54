#include "paging.h"

#include "video.h" // debugging

// paging_mapFirst4MB
// Map the first 4 megabytes into memory so we can enable paging
void paging_mapFirst4MB(){
    kernelPageProcess.directory = paging_allocatePageDirectory();
    kernelPageProcess.tables[0] = paging_allocatePageTable();
    for(int i = 0; i < 1024; i++){
        kernelPageProcess.tables[0]->entries[i] = ((i * 0x1000) | 0x3); // Get the physical address and then set 
    }

    kernelPageProcess.directory->entries[0] = ((uint32_t) kernelPageProcess.tables[0]) | 3;
    kernelPageProcess.directory->entries[768] = ((uint32_t) kernelPageProcess.tables[0]) | 3;
    kernelPageProcess.directory->entries[1024] = ((uint32_t)(kernelPageProcess.directory)) | 3;

    paging_loadPageDirectory(&kernelPageProcess);
}

// paging_allocatePagingProcess
// Create a new Paging_Process
Paging_Process* paging_allocatePagingProcess(){
    Paging_Process* process = (Paging_Process*)paging_allocatePage();
    process->directory = paging_allocatePageDirectory();
    process->tables[0] = paging_allocatePageTable();

    process->directory->entries[0] = ((uint32_t) process->tables[0]) | 3;

    process->tableCount = 1;

    // heap
    process->lastAddr = 0;
    process->heapExtension = 0;
    process->lastFreeChunk = 0;

    return process;
}

// paging_allocatePageDirectory
// Allocate a new directory for a process
Paging_PageDirectory* paging_allocatePageDirectory(){
    Paging_PageDirectory* directory = (Paging_PageDirectory*)paging_allocatePage();
    for(int i = 0; i < 1024; i++){
        directory->entries[i] = 0;
    }
    return directory;
}

// paging_allocatePageTable
// Create a new page table
Paging_PageTable* paging_allocatePageTable(){
    return paging_allocatePageTableAtAddr((void*)paging_allocatePage());
}

// paging_allocatePageTableAtAddr
// Create a new page table at an address
Paging_PageTable* paging_allocatePageTableAtAddr(void* location){
    Paging_PageTable* table = (Paging_PageTable*)location;
    io_print("===New table alloc===\n");
    for(int i = 0; i < 1024; i++){
        char d[6];
        itoa(i, d);
        io_print("Filling ");
        io_print(d);
        io_print(" at ");
        itoa(&table, d);
        io_print(d);
        io_print("\n");
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

    if(!(process->directory->entries[pageDirectoryIdx] & 1)){
        v_terminalWrite("[Pager] Allocating new page table...");
        void* ptr = paging_getPhysicalAddr(process, (void*)paging_allocatePage());
        pageTable = paging_allocatePageTableAtAddr(ptr);
        //pageTable = paging_allocatePageTable();
        process->directory->entries[pageDirectoryIdx] = ((uint32_t) pageTable) | flags | 0x01;
        v_terminalWrite("done.\n");
    }else{
        pageTable = (Paging_PageTable*)(process->directory->entries[pageDirectoryIdx] & 0xFFFFF000);
    }

    pageTable->entries[pageTableIdx] = physicalAddress | (flags & 0xFFF) | 0x01; // we exist 
}

// paging_loadPageDirectory
// Loads a page directory into memory
void paging_loadPageDirectory(Paging_Process* proc){
    asm volatile("mov %0, %%cr3" :: "r"(proc->directory)); // page directory into cr3

    currentlyLoadedProcess = proc;
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
        if(!(memoryFrameBitmap[id] & (1U << bit))){ // This page is free
            memoryFrameBitmap[id] |= (1U << bit);
            return (i * 0x1000);
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
    if((process->directory->entries[pageDirectoryIdx] & 1)){
        return (void*)(process->directory->entries[pageDirectoryIdx] & ~0xFF) + ((unsigned long)virtualAddr & 0xFF);
    }

    return 0;
}

// paging_getCurrentlyLoadedProcess
// Get the current loaded process in cr3
Paging_Process* paging_getCurrentlyLoadedProcess(){
    return currentlyLoadedProcess;
}