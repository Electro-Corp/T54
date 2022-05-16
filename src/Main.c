//#include <string.h>
//#include "csrc/print.h"
// 0xB8000 is the address of the vga framebuffer
// #include <stdint.h>
// typedef uint8_t u8;
// typedef uint16_t u16;
// typedef uint32_t u32;
// typedef uint64_t u64;
char* fb = (char*) 0xB8000;
//void printchar();

//void newprint(u8 printo[20]);
int main() 
{
  int x = 0;
  int y = 0;
  //char str[100];//character array
  int totChar;//variable  declaration
  totChar=0;//variable initialization
  //str.strcpy(printo);
  //strcpy(str, printo);
  int i;
  char printto[100] = "Hello Internet";
  int position = 2 * x + 160 * y;
  for(i=0; printto[i] != '\0'; i++){
    fb[position] = printto[i];
    fb[position + 1] = 0xF0;
    x++;
    position = 2 * x + 160 * y;
    fb[position + 1] = 0xF0;
  }
  
  // //printchar();
  //printchartoscreen("Bro");
  //printchartoscreen("sussy");
  return 0;
}
