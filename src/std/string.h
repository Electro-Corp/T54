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
    while(c[i++]);
    return i;
}

// strcat
// Concanate two strings together
static int strcat(char* root, const char* append){
    int n = strlen(append);
	if (n != 0) {
		char *d = root;
		const char *s = append;
		while (*d != 0) d++;
		do {
			if ((*d = *s++) == 0)
				break;
			d++;
		} while (--n != 0);
		*d = 0;
	}
	return 0;
}

// strcmp
// Compare two strings (0 for match, -1 for not)
static int strcmp(const char* strA, const char* strB){
	int n = strlen(strA), m = strlen(strB);
	if(n != m) return -1;
	for(int i = 0; i < n; i++){
		if(*strA++ != *strB++) return -1;
	}
	return 0;
}

// strcpy
// Copy one string to another
static int strcpy(const char* src, char* dst){
    int n = strlen(src);
    for(int i = 0 ; i < n; i++){
        *dst++ = *src++;
    }
    return 0;
}

// reverse
// Reverse a string
static void reverse(char str[]){
	int i = 0, j = 0;
	char c = 0;
	for(i = 0, j = strlen(str) - 1; i < j; i++, j--){
		c = str[i];
		str[i] = str[j];
		str[j] = c;
	}
}

// itoa
// Integer to ASCII string
static void itoa(int n, char out[]){
	int i, sign;
	if((sign = n) < 0){ // Remember sign
		n = -n; // Make the original num positive
	}

	i = 0;
	// Still getting used to "do while" loops but
	do {
		out[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);

	if(sign < 0) out[i++] = '-';
	out[i++] = '\0';
}
#endif