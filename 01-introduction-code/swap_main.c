/* First C program which only has a main(). Demonstrates proper
   swapping of two int variables declared in main() using a third
   temporary variable. Uses printf() to print results to the screen
   (standard out). Compile run with:

   > gcc swap_main.c
   > ./a.out
*/

#include <stdio.h>                // headers declare existence of functions
                                  // printf in this case
int main(int argc, char *argv[]){ // ENTRY POINT: always start in main()
  int x;                          // declare a variable to hold an integer
  x = 19;                         // set its value to 19
  int y = 31;                     // declare and set a variable
  int tmp = x;                    // declare and set to same value as x
  x = y;                          // put y's value in x's cell
  y = tmp;                        // put tmp's value in y's cell
  printf("%d %d\n",x,y);          // print the values of x and y
  return 0;                       // return from main(): 0 indicates success
}
