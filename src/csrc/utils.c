#include "print.h"
#include "shell/box.h"
#include "kpanic.h"
int lengthofstring(char string[100]){
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
int mid(int x1,int x2, int y1, int y2){
  int midx = (x1+x2)/2;
  int midy = (y1+y2)/2;
  return (midx, midy);
}
int midone(int a,int b){
  return (a+b)/2;
}
void clearscreen(){
  int x,y;
  for (y=0;y<100;y++){
    for(x=0;x<100;x++){
      write2vdu("",64,y,x,6);
    }
  }
}
void fillscreen(int type,char pattern[10]){
  int x,y,num,patterning,ytype;
  if(pattern == "pattern"){
    patterning = 1;
  }
  for (y=0;y<100;y++){
    if(ytype == 0){ytype = 1;}else{ytype = 0;};
    for(x=0;x<100;x++){
      if (patterning == 0){
      write2vdu(" ",64,y,x,type);
      }else{
        if(ytype == 1){
        if(num ==1){
          write2vdu(" ",64,y,x,type);
          num =0;
        }else{
          write2vdu(" ",64,y,x,102);
          num = 1;
        }
        }else{
          if(num ==1){
          write2vdu(" ",64,y,x,102);
          num =0;
        }else{
          write2vdu(" ",64,y,x,type);
          num = 1;
        }
        }
      }
    }
  }
  
}

void *memcpy(void *dest, const void *src, int count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, int count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

int strlen(const char *str)
{
    int retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

//colors:
#define ERROR 0xF4
#define BG 0x33
#define TITLE 0xF1
#define TEXT 0xF0
#define TEXTWITHBG 0x30
#define CLEAR 0x00
//backgrounds
#define BACKGROUNDRED 0x44
#define BACKGROUNDTEST 0x99
#define TERMINAL 0x07
static char *const fb = (char*)0xb8000;

void write2vdu(char ch[1],char attr,int row,int col,int type){
  //char* fb = (char*) 0xB8000;
  
  int x = col;
  int y = row;
  int position = 2 * x + 160 * y;
  fb[position] = ch[0];
  //0xF0
  if(type == 1){
  fb[position + 1] = ERROR;
  }
  if(type == 0){
  fb[position + 1] = BG;
  }  
  if(type == 3){
    fb[position + 1] = TEXT;
  }
  if(type == 5){
    fb[position + 1] = TEXTWITHBG;
  }
  if (type == 4){
    fb[position + 1] = TITLE;
  }
  if(type == 6){
    fb[position + 1] = CLEAR;
  }
  if(type == 101){
    fb[position + 1] = BACKGROUNDRED;
  }
  if(type == 102){
    fb[position + 1] = BACKGROUNDTEST;
  }
  x++;
  position = 2 * x + 160 * y;
  //fb[position + 1] = 0xF0;
}

void terminalwrite(char ch[1], int row,int col){
  static char *const vidptr = (char*) 0xb8000;
  int x = col;
  int y = row;
  int position = 2 * x + 160 * y;
  vidptr[position] = ch[0];
  vidptr[position + 1] = TERMINAL;
  x++;
  position = 2 * x + 160 * y;
}
int removespace(char string[150]){
  char real[150];
  int i;
  int length = lengthofstring(string);
  for (i=0;i<length;i++){
    if(string[i]==" "){
      break;
    }else{
      real[i] = string[i];
    }
  }
  return real;
}
int getbeforespace(char string[150]){
  int length,i;
  for(i=0;i<150;i++){
    if(string[i]==' '|| string[i]=='\0'){
      
      break;
    }else{
      length++;
    }
  }
  return length;
}
//strstr function from GCC standered library
char *
strstr(string, substring)
    register char *string;	/* String to search. */
    char *substring;		/* Substring to try to find in string. */
{
    register char *a, *b;

    /* First scan quickly through the two strings looking for a
     * single-character match.  When it's found, then compare the
     * rest of the substring.
     */

    b = substring;
    if (*b == 0) {
	return string;
    }
    for ( ; *string != 0; string += 1) {
	if (*string != *b) {
	    continue;
	}
	a = string;
	while (1) {
	    if (*b == 0) {
		return string;
	    }
	    if (*a++ != *b++) {
		break;
	    }
	}
	b = substring;
    }
    return "SYSTEM_STRING_ERROR_NULL";
}
char* strcombine(char firstString[1000],char secondString[1000]){
  char based[1000];
  int i,count;
  for(i=0;i<lengthofstring(firstString);i++){
    based[i] = firstString[i];
    count++;
  }
  for(i = 0; i<lengthofstring(secondString);i++){
    based[count] = secondString[i];
    count++;
  }
  return based;
}
#define PORT 0x3F8

// int is_transmit_empty() {
//    return inb(PORT + 5) & 0x20;
// }
 
void write_serial(char a[100]) {
   int i;
   for(i=0;i<lengthofstring(a);i++){
   outb(PORT,a[i]);
    }
}
void splitstring(char string[150]){
  int i,count,length,firstlength;
  firstlength = getbeforespace(string);
  char first[firstlength];
  char rest[100];
  
  length = lengthofstring(string);
  for(i=0;i<length;i++){
    if(string[i]==' '|| string[i]=='\0'){
      //first[i] = "";
      break;
    }else{
      first[i] = string[i];
    }
  }
  //first = removespace(first);
  //printchartoscreen(first,17);
  //messagebox("Got",first,4, 3, 3,8,5);
  if(string[i]=='\0'){
    statusbar("No second part found..");
    return 0;
  }
   statusbar("Finding Second part of string..");
  int real;
  for(i=i;i<length;i++){
      if(string[i]!="\0"){
      //statusbar("At least one cycle occured...");
      rest[real] = string[i];
      real++;
      //printchartoscreen(string[i],9);
      }
    else{
      //printchartoscreen("Broken.....",7);
      break;
    }
  }
  //messagebox("Got",rest,4, 3, 20,8,5);
  statusbar(first[0]);
 // printchartoscreen(rest,11);
  if (strstr(first, "echo") != "SYSTEM_STRING_ERROR_NULL") {
      statusbar("Echo command");
      messagebox("Output",rest,4, 10,15 ,50,5);
  }
  if(strstr(first,"kpanic")!= "SYSTEM_STRING_ERROR_NULL"){
    kpanic("User Triggered Error",first,&first);
  }
  if(strstr(first,"serial")!= "SYSTEM_STRING_ERROR_NULL"){
    //reboot();
    int l = lengthofstring(rest);
    write_serial(rest);
    
    messagebox("Output","Wrote to serial.",4, 10,15 ,50,5);
  }
  if(strstr(first,"div") != "SYSTEM_STRING_ERROR_NULL"){
    int arg1, arg2, quo, rem ;
    messagebox("Output","Calculating.. (will crash)",4, 10,15 ,50,5);
    __asm__ ("movl $0x0, %%edx;"
              "movl %2, %%eax;"
              "movl %3, %%ebx;"
              "cdq; idivl %3" : "=a" (quo), "=&d" (rem) : "a" (arg1), "rm" (arg2));
    messagebox("Output",quo,4, 10,15 ,50,5);


  }
  // else{
  //    char end[100] = ": no such file or command found.";
  //    messagebox("Output",strcombine(first,end),4, 10,15 ,50,5);    
  // }
  //return rest;
}  
// void write2vducolor(char ch[1],char attr,int row,int col,char[3] type){
//   static char *const vidptr = (char*) 0xb8000;
//   int x = col;
//   int y = row;
//   int position = 2 * x + 160 * y;
//   vidptr[position] = ch[0];
//   vidptr[position + 1] = (int)type;
//   x++;
//   position = 2 * x + 160 * y;
// }