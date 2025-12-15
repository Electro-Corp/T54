/*
    T54
    io.h - Input/Output through ports
*/
#ifndef IO_H
#define IO_H

#define COM1 0x3F8

// io_in
// Input from a port
unsigned char io_in(unsigned short p);

// io_out
// Output to a port 
void io_out(unsigned short p, unsigned char d);

// io_print
// Write a string to the serial port
void io_print(unsigned char* str);

#endif