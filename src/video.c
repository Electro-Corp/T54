#include "video.h"

void v_initTerminal(){
    // We initilize the terminal for the first time
    // Init video memory
    v_Buffer = (uint16_t*)VMEM;
    currentRow = 0;
    currentCol = 0;
    // Set color
    tColor = VGA_COLOR_BLACK | VGA_COLOR_LIGHT_GREY << 4;
    // Draw the background 
    for(int i = 0; i < (WIDTH * HEIGHT) + HEIGHT; i++){
        v_terminalPushChar(' ');
    }
    // Reset position
    currentRow = 0;
    currentCol = 0;
}

void v_terminalPutChar(const char c, uint8_t color, int y, int x){
    v_Buffer[y * WIDTH + x] = (uint16_t)c | (uint16_t)color << 8;
}

void v_terminalPushChar(const char c){
    v_terminalPutChar(c, tColor, currentRow, currentCol);
    // Manage row and col
    if(currentCol == WIDTH){ 
        currentCol = 0;
        if(currentRow == HEIGHT){
            v_terminalScroll();
        }else{
            currentRow++;
        }
    }
    else currentCol++;
}

void v_terminalWrite(const char* c){
    for(int i = 0; i < strlen(c) - 1; i++){
        if(c[i] == '\n'){
            if(currentRow == HEIGHT) v_terminalScroll();
            else{
                currentRow++;
            }
            // Reset to next line
            currentCol = 0;
        }else{
            v_terminalPushChar(c[i]);
            v_updateCursor();
        }
    }
    
}

void v_terminalScroll(){
    // I *was* gonna just loop and copy
    // but then I thought, what if I memcpy 
    // the previous stuff
    // and then just redraw the last line
    uint16_t* secondLineStart = &(v_Buffer[2 * WIDTH]);
    memcpy(secondLineStart, v_Buffer, ((WIDTH * HEIGHT) + HEIGHT) - WIDTH);
}

void v_updateCursor(){
    // Generate pos
    uint16_t newPos = (currentRow) * WIDTH + (currentCol);
    // Update by sending to the hardware
    io_out(0x3D4, 0x0F);
    io_out(0x3D5, (uint8_t) (newPos & 0xFF));
    io_out(0x3D4, 0x0E);
    io_out(0x3D5, (uint8_t) ((newPos >> 8) & 0xFF));
}

void v_kPanicScreen(){
    currentRow = 0;
    currentCol = 0;
    // Set color
    tColor = VGA_COLOR_WHITE | VGA_COLOR_BLUE << 4;
    // Draw the background 
    for(int i = 0; i < (WIDTH * HEIGHT) + HEIGHT; i++){
        v_terminalPushChar(' ');
    }
    // Reset position
    currentRow = 0;
    currentCol = 0; 
}

void v_setRow(int n){
    currentRow = n;
}

void v_setCol(int n){
    currentCol = n;
}

int strlen(const char* c){
    int i = 0;
    while(c[i++]){}
    return i;
}