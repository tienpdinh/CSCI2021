// C program which attempts to swap using a function.
// 
// > gcc swap_func.c
// > ./a.out

#include <stdio.h>                // declare existence printf()
void swap(int a, int b);          // function exists, defined below main

int main(int argc, char *argv[]){ // ENTRY POINT: start executing in main()
  int x = 19;                   
  int y = 31;                   
  swap(x, y);                     // invoke function to swap x/y (?)
  printf("%d %d\n",x,y);          // print the values of x and y
  return 0;                     
}

// Function to swap (?) contents of two memory cells
void swap(int a, int b){          // arguments to swap
  int tmp = a;                    // use a temporary to save a
  a = b;                          // a <- b
  b = tmp;                        // b <- tmp=a
  return;
}
