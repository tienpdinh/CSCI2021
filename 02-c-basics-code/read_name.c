// show use of pointer arithmetic to read first and last name into
// same character array

#include <stdio.h>
#include <string.h>                // for strlen()

int main(){
  char name[128];                  // up to 128 chars
  printf("first name: ");          
  scanf(" %s", name);              // read into name
  int len = strlen(name);          // compute length of string
  name[len] = ' ';                 // replace \0 with space
  printf("last name: ");           
  scanf(" %s",name+len+1);         // read last name at offset
  printf("full name: %s\n",name);
  return 0;
}
