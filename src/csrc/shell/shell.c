#include "../print.h"
#include "box.h"
#include "../utils.h"
void initshell(void){
  clearscreen();
  fillscreen(101,"pattern");
  printchartoscreen("T54 Test Screen",1);
  printchartoscreen("Debug Mode: Keyboard Enabled",2);
  printchartoscreen("Shell initilized.",3);
  messagebox("T54","Welcome to T54 0.0.1.",4,4,5,23,6);
 // messagebox("Terminal","Terminal I/O will be here",4,50,4,27,20);
  statusbar("Type anything to continue..");
  topbar("T54 TUI");
}
void terminal_init(void){
  clearscreen();
  // int exit,x,y,i,length;
  // while (exit != 1){
  //   char response[100];
  //   char terminal[100] = "T54>";
  //   char input[100];
  //   length = lengthofstring(terminal);
  //   for(i=0;i<length;i++){
  //     terminalwrite(terminal[i],x,y);
  //     x++;
  //   }
  // }
}