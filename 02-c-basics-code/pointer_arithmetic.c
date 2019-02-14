// Demonstrate basic pointer arithmetic
#include <stdio.h>
void print0_ptr(int *p){            // print int pointed at by p
  printf("%ld: %d\n",(long) p, *p); // address and 0th elem
}
int main(){
  int x = 21;
  int *p;                       // declare a pointer
  int a[] = {5,10,15};          // declare array, auto size
  p = a;                        // point p at a
  print0_ptr(p);
  p = a+1;                      // point p at a plus offset
  print0_ptr(p);
  p++;                          // increase p: pointer arithmetic
  print0_ptr(p);
  p+=2;                         // increase p (!!!)
  print0_ptr(p);
  return 0;
}
