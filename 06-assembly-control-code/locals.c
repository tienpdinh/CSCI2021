int set_buf(char *b, int *s);

int main(){
  int size = -1;
  char buf[16] = "push it";
  int x = set_buf(buf, &size);
  return 0;
}

