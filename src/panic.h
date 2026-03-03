/*
    T54
    panic.h - Kernel Panic 
*/

// kpanic
// Kernel Panic with a specfied message
void kpanic(const char* message);

// kpanic_exceptionNumber
// Kernel Panic with fault code
void kpanic_exceptionNumber(int int_no);