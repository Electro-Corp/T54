#include "proc.h"

#include "video.h" // DEBUG temp


// proc_loadProgram
// Load a program into memory
void* proc_loadProgram(uint8_t* programData){
    Proc_ELFProgram program;
    
    // Load header
    memcpy(programData, &(program.header), sizeof(Proc_ELFHeader));

    // Let's get the program table location
    uint32_t programTableLoc = program.header.e_phoff;
    uint32_t programTableEntriesNum = program.header.e_phnum;

    // Generate program table entries
    if(programTableEntriesNum > 0){

        program.programTableEntries = kmalloc(sizeof(Proc_ELFProgramTableEntry) * programTableEntriesNum);
        memcpy(programData + programTableLoc, program.programTableEntries, sizeof(Proc_ELFProgramTableEntry) * programTableEntriesNum);

        // Allocate program page
        program.proccessPage = paging_allocatePagingProcess();
        
        // Begin loading segments
        for(int i = 0; i < programTableEntriesNum; i++){
            v_terminalWrite("[Proc] Found ");
            switch(program.programTableEntries[i].p_type){
                case PT_NULL:
                    v_terminalWrite("PT_NULL");
                    break;
                case PT_LOAD:
                    v_terminalWrite("PT_LOAD");
                    break;
                case PT_SHLIB:
                    v_terminalWrite("PT_SHLIB");
                    break;
                case PT_HIPROC:
                    v_terminalWrite("PT_HIPROC");
                    break;
                case PT_PHDR:
                    v_terminalWrite("PT_PHDR");
                    break;
                default:
                    v_terminalWrite("[OTHER]");
                    break;
            }
            v_terminalWrite(" program type.\n");
            if(program.programTableEntries[i].p_type == PT_LOAD){
                v_terminalWrite("[Proc] Loading loadable segment...\n");
                // Allocate memory
                void* location = kmalloc_directory(program.proccessPage, program.programTableEntries[i].p_memsz, program.programTableEntries[i].p_vaddr, -1);
                // Store memory location so we can free later
                program.programTableEntries[i].loadedLocation = location;
                // Copy entry data to location
                memcpy(programData + program.programTableEntries[i].p_offset, program.programTableEntries[i].p_vaddr, program.programTableEntries[i].p_memsz);
            }
        }

        // Let's jump 
        uint32_t start = (unsigned long)paging_getPhysicalAddr(program.proccessPage, (void*)(program.header.e_entry));
        //paging_loadPageDirectory(program.proccessPage);

        ///void (*func)() = (void*)(program.header.e_entry);
        //func();


        //jumpToUserMode(elfHeader.e_entry, 0);

        //paging_loadPageDirectory(&kernelPageProcess);
    }else{
        v_terminalWrite("[Proc] ELF file doesn't have any loadable segments..\n");
        return (void*)0;
    }
}

// proc_freeProgram
// Program is finished executing
void proc_freeProgram(Proc_ELFProgram program){
    for(int i = 0; i < program.header.e_phnum; i++){
        if(program.programTableEntries[i].p_type == PT_LOAD){
            free_directory(program.proccessPage, program.programTableEntries[i].loadedLocation);
        }
    }
    free(program.programTableEntries);
}

