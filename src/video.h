/*
    T54
    video.h - video for 80x25 Text mode.
                not used once a higher graphics mode
                is attained
*/

#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>

#include "std/stdlib.h"
#include "io.h"

// Constants
#define WIDTH 80
#define HEIGHT 25
#define VMEM 0xB8000 // VGA memory location

// Color
enum v_Color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1, 
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

// Variables
static int currentRow, currentCol;
static uint8_t tColor;
static uint16_t* v_Buffer;

// v_initTerminal 
// Init terminal background
void v_initTerminal();

// v_terminalPutChar
// Write a character to the terminal
void v_terminalPutChar(const char c, uint8_t color, int y, int x);

// v_terminalPushChar
// Push a character to the terminal, whilst managing position automatically
void v_terminalPushChar(const char c);

// v_terminalWrite
// Write a string to the terminal
void v_terminalWrite(const char* c);

// v_terminalScroll
// Scroll the entire terminal
void v_terminalScroll();

// v_updateCursor
// Update the blinking cursor to our latest position
void v_updateCursor();

// v_kPanicScreen
// Generate a kernel panic screen 
void v_kPanicScreen();

// strlen
// Get length of string
int strlen(const char* c);

#endif