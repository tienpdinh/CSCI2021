// FILE: x_main.c
#include <stdio.h>
#include "x_to_neg8.h"
int x = 0; // conflicts with header
int y = 0;

int main(){
  x_to_neg8();  // set x
  printf("x: %d\n",x);
  printf("y: %d\n",y);
  return 0;
}
