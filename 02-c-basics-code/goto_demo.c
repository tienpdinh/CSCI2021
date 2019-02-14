// Demonstrate control flow with goto
// Low level assembly jumps are similar
#include <stdio.h>
int main(){
  int i=0;
 beginning:      // a label for gotos
  printf("i is %d\n",i);
  i++;
  if(i < 10){
    goto beginning; // go back 
  }
  goto ending;      // go forward
  printf("print me please!\n");
 ending:            // label for goto
  printf("i ends at %d\n",i);
  return 0;
}
