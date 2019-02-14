// Demonstrate void pointer dereferencing and the associated
// shenanigans.  Compiler needs to be convinced to dereference in most
// cases and circumventing the type system (compiler's ability to
// check correctness) is fraught with errors.
#include <stdio.h>
int main(){
  int a = 5;                    // int
  double x = 1.2345;            // double
  void *ptr;                    // pointer to anything

  ptr = &a;
  int b = *((int *) ptr);       // caste to convince compiler to deref
  printf("%d\n",b);

  ptr = &x;
  double y = *((double *) ptr); // caste to convince compiler to deref
  printf("%f\n",y);

  int c = *((int *) ptr);       // kids: this is why types are useful
  printf("%d\n",c);

  return 0;
}
