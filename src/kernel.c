/*
    T54
    kernel.c - C entry point for kernel
*/
#include "video.h"

void k_main(){
    v_initTerminal();
    v_terminalWrite("T54 is starting...");

    return 0;
}