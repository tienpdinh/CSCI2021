// Demonstrate the scanf() function used to read typed input from the
// user.  This function uses addresses of variables to change them to
// the value entered by the user which is NOT possible in most
// programming languages but IS possible in C.

#include <stdio.h>

int main(int argc, char *argv[]){
  int num = -1;                 // inititalize to -1
  printf("enter int: ");        // prompt
  scanf("%d", &num);            // scan and change num by using its addrss
  printf("got %d\n",num);       // show change in num
  return 0;
}
