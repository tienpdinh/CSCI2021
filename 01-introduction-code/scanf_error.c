// Demonstrate a very common error with scanf(): forgetting to pass in
// the address of the location to store a variable that is read
// in. Often this program will yield a "segmentation fault" which is
// when the OS detects the program attempting to access a memory
// outside of the programs allowed range.

#include <stdio.h>

int main(int argc, char *argv[]){
  int num = -1;
  printf("enter int: ");
  scanf("%d", num);             // should be &num: address of num
  printf("got %d\n",num);
  return 0;
}
