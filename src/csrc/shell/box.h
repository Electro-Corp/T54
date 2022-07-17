#ifndef BOX_H_
#define BOX_H_
void write2vdu(char ch[1],char attr,int row,int col,int type);
void messagebox(char titlebar[100],char message[100],int type, int x, int y,int width,int height);
void topbar(char text[100]);
#endif