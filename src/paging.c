#include "paging.h"

#include "video.h" // debugging

// paging_mapFirst4MB
// Map the first 4 megabytes into memory so we can enable paging
void paging_mapFirst4MB(){
    v_terminalWrite("[Paging] Mapping first 4MB of the kernel...\n");

    for(int i = 0; i < 1024; i++){
        kernelFirstTable.entries[i] = ((i * 0x1000) | 0x3); // Get the physical address and then set 
    }

    kernelPageProcess.directory = &kernelPageDirectory;

    kernelPageProcess.directory->entries[0] = ((uint32_t) &kernelFirstTable) | 3;
    kernelPageProcess.directory->entries[768] = ((uint32_t) &kernelFirstTable) | 3;
    kernelPageProcess.directory->entries[1024] = ((uint32_t)(kernelPageProcess.directory)) | 3;

    paging_loadPageDirectory(&kernelPageProcess);
}

// paging_allocatePagingProcess
// Create a new Paging_Process
Paging_Process* paging_allocatePagingProcess(){
    v_terminalWrite("[Paging] Allocating new Paging_Process*\n");
    Paging_Process* process = kmalloc(sizeof(Paging_Process));
    process->directory = paging_allocatePageDirectory();
    process->tables[0] = paging_allocatePageTable();
    v_terminalWrite("table allocated\n");

    //process->directory->entries[0] = ((uint32_t) process->tables[0]) | 3;
    process->directory->entries[0] = ((uint32_t) &kernelFirstTable) | 3;

    process->tableCount = 1;

    // heap
    process->lastAddr = 0;
    process->heapExtension = 0;
    process->lastFreeChunk = 0;

    v_terminalWrite("[Paging] New Paging_Process* allocated.\n");
    return process;
}

// paging_allocatePageDirectory
// Allocate a new directory for a process
Paging_PageDirectory* paging_allocatePageDirectory(){
    Paging_PageDirectory* directory = (Paging_PageDirectory*)kmalloc(sizeof(uint32_t) * 1024);
    for(int i = 0; i < 1024; i++){
        char d[10];
        itoa(i, d);
        io_print("[Directory] Filling ");
        io_print(d);
        io_print(" at ");
        itoa((unsigned long)(directory + (i * sizeof(uint32_t))), d);
        io_print(d);
        io_print(" (diff is  ");
        itoa((unsigned long)((directory + sizeof(Paging_PageDirectory)) - (directory + (i * sizeof(uint32_t)))), d);
        io_print(d);
        io_print(")\n");
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
    //io_print("===New table alloc===\n");
    for(int i = 0; i < 1024; i++){
        // char d[6];
        // itoa(i, d);
        // io_print("Filling ");
        // io_print(d);
        // io_print(" at ");
        // itoa((unsigned long)&table, d);
        // io_print(d);
        // io_print("\n");
        table->entries[i] = 0;
    }
    return table;
}

// paging_mapPage
// Map a physical page to a virtual adderess
void paging_mapPage(Paging_Process* process, uint32_t virtualAddress, uint32_t physicalAddress, uint32_t flags){
    v_terminalWrite("[Pager] Map page!\n");
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
    // Debug
    v_terminalWrite("[Paging] Loading new directory at ");
    char d[10];
    itoa((unsigned long)proc->directory, d);
    v_terminalWrite(d);
    v_terminalWrite("\n");
    // Actual move
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
    for(int i = /*(((unsigned long)&kernelEnd) / 4096)*/ 0; i < MAX_FRAMES; i++){
        uint32_t id = i / 32, bit = i % 32;
        if(!(memoryFrameBitmap[id] & (1U << bit))){ // This page is free
            memoryFrameBitmap[id] |= (1U << bit);
            // 
            v_terminalWrite("[Paging] Allocating a page at ");
            char d[6];
            itoa((i * 0x1000) + (uint32_t)&kernelEnd, d);
            v_terminalWrite(d);
            v_terminalWrite(".\n");
            // 
            return (i * 0x1000) + (uint32_t)&kernelEnd;
        }
    }
    v_terminalWrite("[Paging] No new page found.\n");
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