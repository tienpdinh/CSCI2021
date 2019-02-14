// Demonstrate flavors of constants for various bases
#include <stdio.h>
int main(){
  unsigned int d = 125;                 // decimal
  unsigned int b = 0b1111101;           // binary
  unsigned int h = 0x7D;                // hexadecimal
  unsigned int o = 0175;                // octal

  printf("%d %x %o\n",d,d,d);
  printf("%d %x %o\n",b,b,b);
  printf("%d %x %o\n",h,h,h);
  printf("%d %x %o\n",o,o,o);
  
  return 0;
}
