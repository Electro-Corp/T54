#ifndef UTILS_H_
#define UTILS_H_
int lengthofstring(char string[100]);
int mid(int x1,int x2, int y1, int y2);
int midone(int a,int b);
void clearscreen();
void fillscreen(int type,char pattern[10]);
void *memcpy(void *dest, const void *src, int count);
void *memset(void *dest, char val, int count);
void write2vdu(char ch[1],char attr,int row,int col,int type);
void terminalwrite(char ch[1], int row,int col);
int removespace(char string[150]);
int getbeforespace(char string[150]);

void write_serial(char a[100]);
void splitstring(char string[150]);
// void write2vducolor(char ch[1],char attr,int row,int col,char[3] type);

#endif