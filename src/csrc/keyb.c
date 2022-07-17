#include "portio.h"
#include "keyboardmap.h"
#include "shell/box.h"
#include "terminal/terminal.h"
#include "utils.h"
char history[100000];
int hiscount = 0;
int times = 0;
//
//
char *
instr(string, substring)
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
///
void kb_init(void)
{
    /* This is a very basic keyboard initialization. The assumption is we have a
     * PS/2 keyboard and it is already in a proper state. This may not be the case
     * on real hardware. We simply enable the keyboard interupt */

    /* Get current master PIC interrupt mask */
    unsigned char curmask_master = read_port (0x21);

    /* 0xFD is 11111101 - enables only IRQ1 (keyboard) on master pic
       by clearing bit 1. bit is clear for enabled and bit is set for disabled */
    write_port(0x21, curmask_master & 0xFD);
}
void kb_end(void){
  unsigned char curmask_master = read_port (0x21);

    /* 0xFD is 11111101 - enables only IRQ1 (keyboard) on master pic
       by clearing bit 1. bit is clear for enabled and bit is set for disabled */
    write_port(0x21, curmask_master & 0xF5);
}

/* Maintain a global location for the current video memory to write to */
static int current_loc = 0;
/* Video memory starts at 0xb8000. Make it a constant pointer to
   characters as this can improve compiler optimization since it
   is a hint that the value of the pointer won't change */
static char *const vidptr = (char*) 0xb8000;
char fulltext[1000];
int pos,i,length;
void keyboard_handler(void)
{
    char keycode;

    keycode = read_port(0x60);
    char text = keyboard_map[keycode];
    
    /* Only print characters on keydown event that have
     * a non-zero mapping */
    //if(keycode >= 0 && keyboard_map[keycode]) {
    if(keyboard_map[keycode]) {
      if (text == '\n'){
        //clearscreen();
        length = lengthofstring(fulltext);
        current_loc = current_loc + 4;
        for(i=0;i<=length;i++){
          history[hiscount] = fulltext[i];
          hiscount = hiscount +1;
        }
        history[hiscount] = "|";
        hiscount = hiscount +1;
        if(fulltext != "~"){
        if(instr(fulltext,"history") != "SYSTEM_STRING_ERROR_NULL"){
   messagebox("HISTORY",history,4,50,4,27,20);
        }else{
        splitstring(fulltext); 
        }
        }else{
          serial_write("BRUH");
        }          //printchartoscreen(splitstring(fulltext),100);
          //printchartoscreen(splitstring(fulltext),9);
        
        //vidptr[current_loc++] = 0x07;
        for (i=0;i<=length;i++){
          fulltext[i] = " ";
        }
        char fulltext[1000];
        pos = 0;
      }else{
      fulltext[pos] = text;
       //vidptr[current_loc++] = text;//keyboard_map[keycode];
       //vidptr[current_loc++] = 0x07;
       //printchartoscreen(fulltext,7);
        messagebox("Input",fulltext,4, 10, 10,50,5);
        
       pos ++;
        
      }
        /* Attribute 0x07 is white on black characters */
       //printchartoscreen(text,4);      
      //void terminalwrite(char ch[1], int row,int col);
      //terminalwrite(text,4,current_loc);
       //messagebox("Input",text,1,13,15,4,4);
    }
    /* Send End of Interrupt (EOI) to master PIC */
    write_port(0x20, 0x20);
}
