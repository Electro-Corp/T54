//#include <string.h>
// 0xB8000 is the address of the vga framebuffer
char* fb = (char*) 0xB8000;
void printchartoscreen(char printo[20]);
void printchar(char ch[1]);
void newprint(u8 printo[20]);
int main() 
{
  int x = 0;
  int y = 0;
  //printchar("H");
  printchartoscreen("Bro");
  return 0;
}

void printchartoscreen(char printo[20]){
  int x = 0;
  int y = 0;
  //char str[100];//character array
  int totChar;//variable  declaration
  totChar=0;//variable initialization
  //str.strcpy(printo);
  //strcpy(str, printo);
  int i;
  int position = 2 * x + 160 * y;
  for(i=0; printo[i] != '\0'; i++){
    fb[position] = printo[i];
    fb[position + 1] = 0xF0;
    x++;
    position = 2 * x + 160 * y;
  }
  //free(x);
  //free(y);
}
void printchar(char ch[1]){
  int x = 0;
  int y = 0;
  int position = 2 * x + 160 * y;

  fb[position] = ch;
  fb[position + 1] = 0xF0;
  x++;
  position = 2 * x + 160 * y;
}
void newprint(u8 printo[20]){
  u16 x = 0;
  u16 y = 0;
  u32 position = 2 * x + 2 * 1 * y;
  for(u8 i = 0; printo[i] != '\0'; i++){
    framebuffer[position + 0] = printo[i];
    framebuffer[position + 1] = 0xF0;
    position += 2;
  }
}