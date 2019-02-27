// Computer collatz sequence starting at 10 and return the number of
// steps as the exit code for the program.  Hand-coded assembly
// version of this C code is in col_simple_asm.s but looks
// significantly different from assembly produced from the below using
// gcc.
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  unsigned int n = 10;
  unsigned int s = 0;
  while(n>1){
    if(n % 2 == 1){
      n = n*3 + 1;
    }
    else {
      n = n / 2;
    }
    s++;
  }
  return s;
}
