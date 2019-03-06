#include <stdio.h>

int sum_range(int start, int stop);

int main(){
  int sum1 = sum_range(1,5);
  int sum2 = sum_range(10,15);
  int sum3 = sum_range(20,25);
  int tot = sum1+sum2+sum3;

  // printf("total: %d\n",tot);
  return tot;
}
