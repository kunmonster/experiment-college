#include<iostream>
#include<stdio.h>
#include<stdlib.h>
int main(){
  FILE * fp ;
  
  fp = fopen("D:/vscode/c++Gitrepo/algorithm/work.png","rb");
  if(fp){
    char ch;
    while((ch=getc(fp)) != EOF){
      putchar(ch);
    }
  }
  return 0;
}