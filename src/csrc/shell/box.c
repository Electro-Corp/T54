#include "../utils.h"

void messagebox(char titlebar[100],char message[100],int type, int x, int y,int width,int height){
  int r,c,i,initr,cmax,cstart,bot;
  initr = y;
  cmax = x+width;
  cstart = x;
  bot = initr+height;
  for (r=initr;r<=bot;r++){
    for (c = cstart; c<=cmax;c++){
      if(r!=initr && r!=bot){
      if(c!=cstart && c!=cmax){
      write2vdu("",64,r,c,0);
      }else{
        if(c==cstart){
          write2vdu("|",64,r,c,3);
        }
        if(c==cmax){
          write2vdu("|",64,r,c,3);
        }
      }
      }
      else{
          write2vdu("-",64,r,c,type);
        
      }
    }
  }
  //message
  c=50;  
  int length = lengthofstring(message);
  int midx = midone(x,cmax);
  midx = midx-(length/2);
  
  for(i=0;i<=length;i++){
    //write2vdu(&(message[i]),77,(bot)/2,(i+(cmax/2)-(length/2))+2,5);
    //int midx, midy = mid(x,cmax,)
    
    
    //write2vdu(&(message[i]),77,(bot/2)+(initr/2),(i+(cmax/2)-(length/2))+2,5);
    
    
      write2vdu(&(message[i]),77,(bot/2)+(initr/2),midx+i,5);
    
  }
  //titlebar
  length = lengthofstring(titlebar);
  midx = midone(x,cmax);
  midx = midx-(length/2);
  for(i=0;i<=length;i++){
    //write2vdu(&(titlebar[i]),77,initr,(i+(cmax/2)-(length/2))+2+1,3);
    write2vdu(&(titlebar[i]),77,initr,midx+i,3);
  }
}
void topbar(char message[100]){
  int i,length,midx;
  length = lengthofstring(message);
  midx = 200;//midone(0,360);
  midx = midx-(length/2);
  for(i = 0;i<=399;i++){
    write2vdu("",69,-4,i,4);
  }
  for(i = 0;i<=length;i++){
    //char ch[1],char attr,int row,int col,int type
    if(message[i]!=""){
      write2vdu(&(message[i]),69,-2,midx+i,4);
    }
  }
}
void statusbar(char status[100]){
  int i,length,midx;
  length = lengthofstring(status);
  midx = 200;//midone(0,360);
  midx = midx-(length/2);
  for(i = 0;i<=399;i++){
    write2vdu("",69,24,i,4);
  }
  for(i = 0;i<=length;i++){
    //char ch[1],char attr,int row,int col,int type
    write2vdu(&(status[i]),69,24,0+i,4);
  }
}