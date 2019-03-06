#include <stdlib.h>
// C code that inspired jmp_tests_asm.s. Note that moving everything
// into main() may result in the compiler optimizing out to simply
// returning the final answer number.

int func(int edi, int esi, int *edx, int ecx){
  int eax = 0;
  if(esi == 0){
    eax += 20;
  }
  if(esi){
    eax += 30;
  }
  if(edx != NULL){
    eax += 40;
  }
  if(ecx < 0){
    eax += 50;
  }
  return eax;
}  

int main(){
  int eax = 0;

  int edi = 5;
  int esi = 3;
  int *edx = 0;
  int ecx = -4;
  int ret = func(edi,esi,edx,ecx);
  return ret;
}
