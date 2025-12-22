/*
    T54 
    stdlib.h - memory and other various things
*/
#ifndef STDLIB_H
#define STDLIB_H

// memcpy
// Copy memory from buffer to buffer
static void* memcpy(const void* srcPtr, const void* dstPtr, int size){
    unsigned char* dst = (unsigned char*) dstPtr;
	const unsigned char* src = (const unsigned char*) srcPtr;
	for (int i = 0; i < size; i++)
		dst[i] = src[i];
	return dst;
}

// memset
// Set memory
static void* memset(const void* aPtr, char value, int size){
	unsigned char* dst = (unsigned char*) aPtr;
	for(int i = 0; i < size; i++){
		dst[i] = value;
	}
	return dst;
}

#endif