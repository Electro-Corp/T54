#include "io.h"

unsigned char io_in(unsigned short p){
	unsigned char rv;
	__asm__ __volatile__("inb %1, %0" : "=a" (rv) : "dN" (p));
	return rv;
}

void io_out(unsigned short p, unsigned char d){
	__asm__ __volatile__("outb %1, %0" : : "dN" (p), "a" (d));
}

void io_insw(uint16_t port, void* buf, unsigned long n){
	__asm__ __volatile__("cld; rep; insw" : "+D"(buf), "+c"(n) : "d"(port));
}

void io_outsw(uint16_t port, const void* buf, unsigned long n){
	__asm__ __volatile__("cld; rep; outsw" : "+S"(buf), "+c"(n) : "d"(port));
}

void io_print(unsigned char* str){
	for(int i = 0; i < strlen(str); i++){
		io_out(COM1, str[i]);
	}
}
