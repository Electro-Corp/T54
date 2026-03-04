/*
    A test program for T54
*/

int _start(){
    int a = 0;
    a = 2 + 5;

    asm("mov 0x4c, %dl\n"
    "mov $'H', %al\n"
    "movb %al, 0xB8000\n"
    "movb %dl, 0xB8001");
    return 0;
}
