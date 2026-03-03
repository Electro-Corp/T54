#include "proc.h"

#include "video.h" // DEBUG temp

// proc_loadHeader
// Just load a program's header
Proc_ELFHeader proc_loadHeader(uint8_t* program){
    Proc_ELFHeader header;

    memcpy(program, &header, sizeof(header));

    return header;
}

// proc_loadProgram
// Load a program into memory
void* proc_loadProgram(uint8_t* programData){
    Proc_ELFProgram program;
    // Load header
    Proc_ELFHeader elfHeader = proc_loadHeader(programData);
    program.header = elfHeader;
    // Let's get the program table location
    uint32_t programTableLoc = elfHeader.e_phoff;
    uint32_t programTableEntriesNum = elfHeader.e_phnum;

    // Generate program table entries
    if(programTableEntriesNum > 0){
        program.programTableEntries = malloc(sizeof(Proc_ELFProgramTableEntry) * programTableEntriesNum);
        memcpy(programData + programTableLoc, program.programTableEntries, sizeof(Proc_ELFProgramTableEntry) * programTableEntriesNum);
    }else{
        v_terminalWrite("[Proc] ELF file doesn't have any loadable segments..\n");
        return;
    }

}

// proc_freeProgram
// Program is finished executing
void proc_freeProgram(Proc_ELFProgram program){
    free(program.programTableEntries);
}

