#include "keyboard.h"

// keyboard_handleInterrupt
// Handle keyboard input
void keyboard_handleInterrupt(struct regs *r){
    unsigned char code;
    // Read from keyboard data buffer
    code = io_in(0x60);
    
    // Top bit set? 
    if(code & 0x80){
        // Something has been released
    }else{
        lastCharacter = keyTable[code];
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