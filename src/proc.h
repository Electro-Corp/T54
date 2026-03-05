/*
    T54
    proc.h - Header for processes
*/
#ifndef PROC_H
#define PROC_H

#include <stdint.h>

#include "std/stdlib.h"
#include "memory.h"
#include "paging.h"

//
// ELF loading
//

typedef uint32_t Elf32_Addr;
typedef short Elf32_Half;
typedef uint32_t Elf32_Off;
typedef uint32_t Elf32_Sword;
typedef uint32_t Elf32_Word;

#define EI_NIDENT 16

// From the ELF specfication
typedef struct{
    unsigned char e_ident[EI_NIDENT];
    Elf32_Half e_type; // Object type (None, Relocatable file, etc)
    Elf32_Half e_machine; // Machine designed for
    Elf32_Word e_version; // ELF Version
    Elf32_Addr e_entry; // Virtual adderess to transfer control to
    Elf32_Off e_phoff; // Offset of the program table
    Elf32_Off e_shoff; // Offset of the section table
    Elf32_Word e_flags; // Flags
    Elf32_Half e_ehsize; // Header size
    Elf32_Half e_phentsize; // One program entry size
    Elf32_Half e_phnum; // Number of entries in the program table
    Elf32_Half e_shentsize; // One section entry size
    Elf32_Half e_shnum; // Number of entries in the section table
    Elf32_Half e_shstrndx; // Section index for string table
} Proc_ELFHeader;

typedef enum {
    PT_NULL = 0,  // Unused
    PT_LOAD = 1, // A loadable segment 
    PT_DYNAMIC = 2, // Dynamic linking
    PT_INTERP = 3, // Invoke some path as an interpeter
    PT_NOTE = 4, // Random info
    PT_SHLIB = 5, // Unspecfied
    PT_PHDR = 6, // location and size of the program header itself
    PT_LOPROC = 0x70000000, // processor specfic
    PT_HIPROC = 0x7fffffff // ^^^^
} Proc_ELFPSegmentType;

typedef struct{
    Elf32_Word p_type;  // What kind of segment this is (see Proc_ELFPSegmentType)
    Elf32_Off p_offset; // Offset from the start of the file where this resides
    Elf32_Addr p_vaddr; // Virtual address where this resides
    Elf32_Addr p_paddr; // Physical address where this resides
    Elf32_Word p_filesz; // File image size
    Elf32_Word p_memsz; // Memory image size
    Elf32_Word p_flags; // Flags
    Elf32_Word p_align; // Alignment

    // This is for the OS to know
    void* loadedLocation;
} Proc_ELFProgramTableEntry;

typedef struct {
    Proc_ELFHeader header;
    Proc_ELFProgramTableEntry* programTableEntries;

    Paging_Process* proccessPage;
} Proc_ELFProgram;

extern void jumpToUserMode(uint32_t entry, uint32_t stack);

// proc_loadProgram
// Load a program into memory
void* proc_loadProgram(uint8_t* programData);

// proc_freeProgram
// Program is finished executing
void proc_freeProgram(Proc_ELFProgram program);

#endif