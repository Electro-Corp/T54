void printchartoscreen(char printo[200],int line){
  //char* fb = (char*) 0xB8000;
  //char* fb = (char*) 0xb8000;
  static char *const fb = (char*) 0xb8000;

  int x = 0;
  int y = line;
  //char str[100];//character array
  int totChar;//variable  declaration
  totChar=0;//variable initialization
  //str.strcpy(printo);
  //strcpy(str, printo);
  int i;
  int position = 2 * x + 160 * y;
  for(i=0; printo[i] != '\0'; i++){
    fb[position] = printo[i];
    fb[position + 1] = 0xF0;
    x++;
    position = 2 * x + 160 * y;
    fb[position + 1] = 0xF0;
  }
  //free(x);
  //free(y);
}