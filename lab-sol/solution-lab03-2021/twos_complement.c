// Demonstrate two's complement in C
#include <stdio.h>
int main(){
  char num = 124;               // initial signed positive number
  char neg = ~(num-1);          // negate: subtract 1 and then binary invert, the ~ operator
  char pos = (~neg) + 1;        // positive: invert then add 1
  printf("%d %d %d\n",          // print number, negated version, and positive
         num,neg,pos);
  return 0;
}
