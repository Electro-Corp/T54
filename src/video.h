/*
    T54
    video.h - video for 80x25 Text mode.
                not used once a higher graphics mode
                is attained
*/

#ifndef VIDEO_H
#define VIDEO_H

// Constants

#define WIDTH 80
#define HEIGHT 25
#define VMEM 0xB8000 // VGA memory location



// v_initTerminal 
// Init terminal background and shi
void v_initTerminal();

#endif