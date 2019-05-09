// FILE: xy_int.c
int x=0;        // global vars
int y=0;        // strongly defined

void x_to_neg8(); // in different .o

#include <stdio.h>
int main(){
  x_to_neg8();  // set x only
  printf("x: %d\n",x);
  printf("y: %d\n",y);
  return 0;
}
