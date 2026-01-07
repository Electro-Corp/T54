/*
    T54 
    string.h - string utilities
*/
#ifndef STRING_H
#define STRING_H

// strlen
// Get length of string
static int strlen(const char* c){
    int i = 0;
    while(c[i++]){}
    return i;
}
#endif