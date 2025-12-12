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
    for(int i = 0; i < strlen(c); i++){
        v_terminalPushChar(c[i]);
    }
}

void v_terminalScroll(){
    // 
}

int strlen(const char* c){
    int i = 0;
    while(c[i++]){}
    return i;
}