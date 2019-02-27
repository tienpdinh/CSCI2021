// Call code in divide.s to demonstrate division
// Compile with
// > gcc division_main.c division.s

#include <stdio.h>
#include <stdlib.h>

int div_small();
long div_big();

int main(int argc, char *argv[]){
  int sm = div_small();
  printf("div_small() is: %d\n",sm);

  long bg = div_big();
  printf("div_big() is: %ld\n",bg);

  return 0;
}
