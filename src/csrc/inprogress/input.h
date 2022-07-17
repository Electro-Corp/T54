#ifndef INPUT_H_
#define INPUT_H_
typedef struct{
  int bruh;
} input; 
int getInput();
unsigned int restart_keyboard();
unsigned char get_scancode();
void outb( unsigned short port, unsigned char val );
static __inline unsigned char inb (unsigned short int port);
void init_pics(int pic1, int pic2);
#endif
