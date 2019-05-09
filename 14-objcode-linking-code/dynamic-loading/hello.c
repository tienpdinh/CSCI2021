#include <stdio.h>

long is_defined[10] = {};
int  not_defined[4];

int main(int argc, char *argv[]){
  printf("Hello World!\n");
  int i = 32;
  double x = 1.234;
  printf("My favorite int is %d and float is %f\n",
         i,x);

  return 0;
}
