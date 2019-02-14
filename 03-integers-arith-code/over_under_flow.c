// Simple demonstration of overflow and underflow
#include <stdio.h>
int main(){
  unsigned char a,b,c;   // 8-bit positive only
  a = 169;               // Demo overflow
  b = 193;
  c = a + b;
  printf("%d + %d = %d\n",a,b,c);
  if(c < a && c < b){
    printf("overflow: sum less than summands\n");
  }
  a = 5;                 // Demo underflow
  b = 50;
  c = a - b;
  printf("%d - %d = %d\n",a,b,c);
  if(c > a){
    printf("underflow: difference larger than a\n");
  }
  return 0;
}
  
