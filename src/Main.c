#include "csrc/shell/shell.h"
#include "csrc/idt.h"
#include "csrc/inprogress/input.h"
#include "csrc/portio.h"
char* fb = (char*) 0xB8000;
unsigned int restart_keyboard();
volatile unsigned char ScanCode;
void irq_01();
int randomnum(){
  int num;  
  return num;
}
static unsigned int g_seed;
inline void fast_srand(int seed) {
    g_seed = seed;
}
int start,x,y;
x = 2;
y = 2;
int xmax,xmin,ymax,ymin;
char c;     
// KEYBOARD HANDLING

#define IDT_SIZE 256
#define PIC_1_CTRL 0x20
#define PIC_2_CTRL 0xA0
#define PIC_1_DATA 0x21
#define PIC_2_DATA 0xA1

void keyboard_handler_int();
void load_idt(void*);

struct idt_entry
{
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char flags;
    unsigned short int offset_higherbits;
} __attribute__((packed));

struct idt_pointer
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry idt_table[IDT_SIZE];
struct idt_pointer idt_ptr;

void load_idt_entry(int isr_number, unsigned long base, short int selector, unsigned char flags)
{
    idt_table[isr_number].offset_lowerbits = base & 0xFFFF;
    idt_table[isr_number].offset_higherbits = (base >> 16) & 0xFFFF;
    idt_table[isr_number].selector = selector;
    idt_table[isr_number].flags = flags;
    idt_table[isr_number].zero = 0;
}

static void initialize_idt_pointer()
{
    idt_ptr.limit = (sizeof(struct idt_entry) * IDT_SIZE) - 1;
    idt_ptr.base = (unsigned int)&idt_table;
}

static void initialize_pic()
{
    /* ICW1 - begin initialization */
    write_port(PIC_1_CTRL, 0x11);
    write_port(PIC_2_CTRL, 0x11);

    /* ICW2 - remap offset address of idt_table */
    /*
    * In x86 protected mode, we have to remap the PICs beyond 0x20 because
    * Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
    */
    write_port(PIC_1_DATA, 0x20);
    write_port(PIC_2_DATA, 0x28);

    /* ICW3 - setup cascading */
    write_port(PIC_1_DATA, 0x00);
    write_port(PIC_2_DATA, 0x00);

    /* ICW4 - environment info */
    write_port(PIC_1_DATA, 0x01);
    write_port(PIC_2_DATA, 0x01);
    /* Initialization finished */

    /* mask interrupts */
    write_port(0x21 , 0xff);
    write_port(0xA1 , 0xff);
}

void idt_init()
{
    initialize_pic();
    initialize_idt_pointer();
    load_idt(&idt_ptr);
}

// struct interrupt_frame;
 
// __attribute__((interrupt)) void interrupt_handler(struct interrupt_frame* frame)
// {
//     gpfExcHandler();
// }
int main() {
  if (start == 0){
    //clearscreen();
    initshell();
    start = 1;
  }
  
  initshell();
  idt_init();
  load_idt_entry(0x21, (unsigned long) keyboard_handler_int, 0x08, 0x8e);
  kb_init();

  
 return 0;
              
}


