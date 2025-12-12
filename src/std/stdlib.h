/*
    T54 
    stdlib.h - memory and other various things
*/

// memcpy
// Copy memory from buffer to buffer
static void* memcpy(const void* aPtr, const void* bPtr, int size){
    unsigned char* dst = (unsigned char*) bPtr;
	const unsigned char* src = (const unsigned char*) aPtr;
	for (int i = 0; i < size; i++)
		dst[i] = src[i];
	return dst;
}