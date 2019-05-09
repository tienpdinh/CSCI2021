// FILE: big_data.c
long arr[20000] = {1,2,3};
int main(){
  for(int i=0; i<1024; i++){
    arr[i] = i;
  }
  return 0;
}
