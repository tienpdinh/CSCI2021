// FILE: func_int.c
void negate(int *a); // in different .o

#include <stdio.h>
int main(){
  int x = 2;
  int y = 0;
  negate(&x);
  printf("x: %d\n",x);
  printf("y: %d\n",y);
  return 0;
}
