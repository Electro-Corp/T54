#include "keyboard.h"

// keyboard_handleInterrupt
// Handle keyboard input
void keyboard_handleInterrupt(struct regs *r){
    unsigned char code;
    // Read from keyboard data buffer
    code = io_in(0x60);
    
    // Converted char
    char c;

    // Top bit set? 
    if(code & 0x80){
        // Something has been released

        // Release Shift (it's 170 for some reason?)
        if(code == 170 || c == RIGHT_SHIFT){
            shiftHeld = 0;
        }

        lastCharacter = 0;
    }else{
        c = keyTable[code];

        // Shift check
        if(code == 42 || c == RIGHT_SHIFT){
            shiftHeld = 1;
            c = 0; // Don't print shift
        }
        // Are we holding shift?
        else if(shiftHeld == 1){ 
            // Alphabet shift
            if(c >= 97 && c <= 122) c -= 32;
            // Number shift (1 thru 7)
            else if(c >= 49 && c <= 55) c -=  16;
        }

        lastCharacter = c;
    }
}

// keyboard_clearBuffer
// Clear the buffer
void keyboard_clearBuffer(){
    lastCharacter = 0;
}

// keyboard_clearBuffer
// Get the last char and clear buffer
char keyboard_popLastChar(){
    char tmp = lastCharacter;
    keyboard_clearBuffer();
    return tmp;
}