//#include <string.h>
#include "csrc/print.h"
#include "csrc/input.h"
#include "csrc/error.h"
// 0xB8000 is the address of the vga framebuffer
// #include <stdint.h>
// typedef uint8_t u8;
// typedef uint16_t u16;
// typedef uint32_t u32;
// typedef uint64_t u64;
char* fb = (char*) 0xB8000;
unsigned int restart_keyboard();
volatile unsigned char ScanCode;
void irq_01();
//void printchar();
//char input[100] = "";
//void newprint(u8 printo[20]);
int start = 0;
int main() 
{
    
  // int x = 0;
  // int y = 0;
  // //char str[100];//character array
  // int totChar;//variable  declaration
  // totChar=0;//variable initialization
  //str.strcpy(printo);
  //strcpy(str, printo);
  // int i;
  // char printto[1000] = "Starting T54..";
  // int position = 2 * x + 160 * y;
  // for(i=0; printto[i] != '\0'; i++){
  //   fb[position] = printto[i];
  //   fb[position + 1] = 0xF0;
  //   x++;
  //   position = 2 * x + 160 * y;
  //   fb[position + 1] = 0xF0;
  // }
  
  // //printchar();
  if (start == 0){
  printchartoscreen("Starting T54",0);
  printchartoscreen("T54 development build 0.1",1);
  printchartoscreen("Terminal will load soon",2);
  error("Segmentation Fault (L bozo)",3);
    start = 1;
  }
  getInput();
  //printchartoscreen(input,3);
  return 0;
}



// void irq_01() {
//         out(0x20, 0x20);   // Send EOI
//         ScanCode = in(0x60);     
//         if((ScanCode & 128) == 128)
//                  printchartoscreen("PRESSED!!",6);
//         else
//                 printchartoscreen("NOPE",6);
// }