/**
 * T54
 * gdt.c - manages our GDT
 */
 
// One GDT entry
struct gdt_entry{
    unsigned short limit_L;
    unsigned short base_L;
    unsigned char base_M;
    unsigned char access;
    unsigned char gran;
    unsigned char base_H;
} __attribute__((packed));

// Pointer with the limit (max bytes taken up by GDT - 1)
struct gdt_ptr{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

// One gdt, with three entries
struct gdt_entry gdt[3];
// Pointer to gdt 
struct gdt_ptr gp;

// ASM function to reload segment registers
extern void gdt_flush();

// gdt_setGate
// Set a desc in the GDT
void gdt_setGate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran){
    // Setup base addr
    gdt[num].base_L = (base & 0xFFFF);
    gdt[num].base_M = ((base >> 16) & 0xFFFF);
    gdt[num].base_H = ((base >> 24) & 0xFFFF);
    // Setup desc limit
    gdt[num].limit_L = (limit & 0xFFFF);
    gdt[num].gran = ((limit >> 16) & 0x0F);
    // Setup gran
    gdt[num].gran |= (gran & 0xF0);
    gdt[num].access = access;
}

// gdt_install
// Install our GDT
void gdt_install(){
    // Setup GDT pointer/limit
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = &gdt;

    // Null sec
    gdt_setGate(0,0,0,0,0);
    // Code segment
    //     entry  bAddr  limit (4gb)     4kb gran
    gdt_setGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    // Data segment
    // almost same as code, but different descriptor for data
    gdt_setGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    // Flush
    gdt_flush();
}