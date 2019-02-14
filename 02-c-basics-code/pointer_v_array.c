// Demonstrate equivalence of pointers and arrays
#include <stdio.h>
void print0_arr(int a[]){             // print 0th element of a
  printf("%ld: %d\n",(long) a, a[0]); // address and 0th elem
}
void print0_ptr(int *p){            // print int pointed at by p
  printf("%ld: %d\n",(long) p, *p); // address and 0th elem
}
int main(){
  int *p = NULL;                // declare a pointer, points nowhere
  printf("%ld: %ld\n",          // print address/contents of p
         (long) &p, (long)p);   // by casting to 64 bit long
  int x = 21;                   // declare an integer
  p = &x;                       // point p at x
  print0_arr(p);                // pointer as array
  int a[] = {5,10,15};          // declare array, auto size
  print0_ptr(a);                // array as pointer
  //a = p;                      // can't change where array points
  p = a;                        // point p at a
  print0_ptr(p);
  return 0;
}
