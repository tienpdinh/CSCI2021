// FILE: big_bss.c
long arr[20000] = {};
int main(){
  for(int i=0; i<1024; i++){
    arr[i] = i;
  }
  return 0;
}
