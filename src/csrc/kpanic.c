#define TEXTWITHBG 0x1F
char* fbk = (char*) 0xB8000;
//#include "keyb.c"
void write2vduk(char ch[1],char attr,int row,int col,int type){

  int x = col;
  int y = row;
  int position = 2 * x + 160 * y;
  fbk[position] = ch[0];
  //0xF0
  if(type == 6){
  fbk[position + 1] = 0x11;
  }
  if(type == 999){
  fbk[position + 1] = TEXTWITHBG;
  }

  x++;
  position = 2 * x + 160 * y;
  //fb[position + 1] = 0xF0;
}
void kclear(){
  int x,y;
  for (y=0;y<100;y++){
    for(x=0;x<100;x++){
      write2vduk("",64,y,x,6);
    }
  }
}
void printline(char printo[200],int line){
  //char* fb = (char*) 0xB8000;
  //char* fb = (char*) 0xb8000;


  int x = 0;
  int y = line;
  //char str[100];//character array
  int totChar;//variable  declaration
  totChar=0;//variable initialization
  //str.strcpy(printo);
  //strcpy(str, printo);
  int i;
  int position = 2 * x + 160 * y;
  for(i=0; printo[i] != '\0'; i++){
    fbk[position] = printo[i];
    fbk[position + 1] = TEXTWITHBG;
    x++;
    position = 2 * x + 160 * y;
    fbk[position + 1] = TEXTWITHBG;
  }
  //free(x);
  //free(y);
}
int lengthofstringk(char string[100]){
  int length,i;
  for (i=0;i<100;i++){
    if(string[i]){
      length+=1; 
    }else{
      break;
    }
  }
  return length;
}
void topbark(char message[100],int boi){
  int i,length,midx;
  length = lengthofstringk(message);
  midx = 200;//midone(0,360);
  midx = midx-(length/2);
  for(i = 0;i<=399;i++){
    write2vduk("",69,-4,i,6);
  }
  for(i = 0;i<=length;i++){
    //char ch[1],char attr,int row,int col,int type
    write2vduk(&(message[i]),69,-2,midx+i,999);
  }
}
void statusbark(char status[100]){
  int i,length,midx;
  length = lengthofstring(status);
  midx = 200;//midone(0,360);
  midx = midx-(length/2);
  for(i = 0;i<=399;i++){
    write2vdu("",69,24,i,6);
  }
  for(i = 0;i<=length;i++){
    //char ch[1],char attr,int row,int col,int type
    write2vdu(&(status[i]),69,24,midx+i,999);
  }
}
int mem(void){
    unsigned short total;
    unsigned char lowmem, highmem;
 
    outportb(0x70, 0x30);
    lowmem = inportb(0x71);
    outportb(0x70, 0x31);
    highmem = inportb(0x71);
 
    total = lowmem | highmem << 8;
    return total;
}
int nestexc = 0;
 
// called by the stub
void gpfExcHandler(void) {
   //if (nestexc > MAX_NESTED_EXCEPTIONS)     
   //kpanic();
   nestexc++;
 
   // if (!fix_the_error()) {
   //   write_an_error_message();
   // }
   kpanic("UNKNOWN KERNEL ERROR","UNKNOWN","0");
   nestexc--;
   return;
}
__attribute__((noreturn))
void exception_handler(void);
void exception_handler() {
    kpanic("UNKNOWN KERNEL ERROR","UNKNOWN","0");
    __asm__ volatile ("cli; hlt"); // Completely hangs the computer
}
void kpanic(char error[100], char command[100],char add[100]){
  unsigned int based;
  based = 0/0;
  // asm( 
  //   "mov cr6, eax;"
  // );
  
  kb_end();
  kclear();
  //printline("-------- KERNEL PANIC ---------",0);
  topbark("KERNEL PANIC",-4);
  printline("T54 ran into an unrecoverable error. Please Restart. Details:",1);
  printline(" ",2);
  printline(error,3);
  printline(" ",4);
  printline("The problem seems to be with this command : ",5);
  printline(command,6);
  printline(" ",7);
  printline(mem(),8);
  statusbark("END KERNEL PANIC");
  //printline("ERROR ERROR ERROR ERROR",100000000000);
}