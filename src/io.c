#include "io.h"

// io_in
// Input from a port (8)
unsigned char io_in(unsigned short p){
	unsigned char rv;
	__asm__ __volatile__("inb %1, %0" : "=a" (rv) : "dN" (p));
	return rv;
}

// io_out
// Output to a port 
void io_out(unsigned short p, unsigned char d){
	__asm__ __volatile__("outb %1, %0" : : "dN" (p), "a" (d));
}

// io_insw
// Input from port (16)
void io_insw(uint16_t port, void* buf, unsigned long n){
	__asm__ __volatile__("cld; rep; insw" : "+D"(buf), "+c"(n) : "d"(port));
}

// io_outsw
// Output to a port (16)
void io_outsw(uint16_t port, const void* buf, unsigned long n){
	__asm__ __volatile__("cld; rep; outsw" : "+S"(buf), "+c"(n) : "d"(port));
}

// io_print
// Write a string to the serial port
void io_print(unsigned char* str){
	for(int i = 0; i < strlen(str); i++){
		io_out(COM1, str[i]);
	}
}
