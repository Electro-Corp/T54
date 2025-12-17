/*
    T54
    io.h - Input/Output through ports
*/
#ifndef IO_H
#define IO_H

#include <stdint.h>

#define COM1 0x3F8

// io_in
// Input from a port (8)
unsigned char io_in(unsigned short p);

// io_out
// Output to a port 
void io_out(unsigned short p, unsigned char d);

// io_insw
// Input from port (16)
void io_insw(uint16_t port, void* buf, unsigned long n);

// io_outsw
// Output to a port (16)
void io_outsw(uint16_t port, const void* buf, unsigned long n);

// io_print
// Write a string to the serial port
void io_print(unsigned char* str);

#endif