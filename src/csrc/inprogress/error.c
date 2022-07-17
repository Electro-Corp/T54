#include "../print.h"
int error(char error[100],int line){
  char finalerror[1000] = "Error: ";
  int i;
  for(i=0; error[i] != '\0'; i++){
    finalerror[1001+i] = error[i];
  }
  return finalerror;
}
