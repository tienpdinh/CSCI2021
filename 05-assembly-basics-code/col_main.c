// Collatz sequence computation based on command line
// argument. Compile to see various assembly language versions using
// > gcc -S -Og col_main.c  # debug optimization (none)
// > gcc -S col_main.c      # default optimization
// > gcc -S -O3 col_main.c  # heavy optimization

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  int n = atoi(argv[1]);
  int s = 0;
  printf("step %2d: %d\n",s,n);
  while(n>1){
    if(n % 2 == 1){
      n = n*3 + 1;
    }
    else {
      n = n / 2;
    }
    s++;
    printf("step %2d: %d\n",s,n);
  }
  return 0;
}
