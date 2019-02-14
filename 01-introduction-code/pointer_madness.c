// Demonstration of the * symbol to multiply, declare pointers,
// dereference. Combinations in a single line shown.  Also shows a
// form of pointer arithmetic.

#include <stdio.h>

int main(){

  int a = 5;
  int b = 3 * 4;                // Multiplication
  int c[4] = {1, 3, 5, 9};

  int *x = &a;                  // Declare pointers
  int *y = &b;
  int w = *x;                   // Dereference pointer
  printf("w is %d\n",w);

  int *p = c;                   // Point at beginning of array

  int z = *x * *y + *(p+2);     // Multiply and deref, pointer addition

  printf("z is %d\n",z);
  return 0;
}
