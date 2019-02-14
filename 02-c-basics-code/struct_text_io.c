// Demonstrate use text file I/O functions with structs uses fprintf()
// and fscanf() to write/read formatted versions of the struct
#include <stdlib.h>
#include <stdio.h>

typedef struct {                // simple struct 
  double x;     int y;    char nm[4];
} small_t;

int main(){
  small_t sarr[3] = {
    {.x=5.5,  .y=2, .nm = "oh"},
    {.x=15.5, .y=4, .nm = "my"},
    {.x=25.5, .y=6, .nm = "god"},
  };

  char *struct_file = "structs.txt";             // name of file

  FILE *fout = fopen(struct_file,"w");           // open for writing
  for(int i=0; i<3; i++){
    fprintf(fout,"%f %d %s\n",                   // print struct data
            sarr[i].x, sarr[i].y, sarr[i].nm);   // to file, text format
  }
  fclose(fout);                                  // close output file

  small_t *darr = malloc(sizeof(small_t)*3);     // dynamically allocate array
  FILE *fin = fopen(struct_file,"r");            // open file for reading
  for(int i=0; i<3; i++){
    fscanf(fin,"%lf %d %s\n",                    // read struct data into
           &darr[i].x, &darr[i].y, darr[i].nm);  // struct array
  }
  fclose(fin);                                   // close input file
  
  for(int i=0; i<3; i++){                        // print read array
    fprintf(stdout,"%f %d %s\n",                 // use open stdout to print
            darr[i].x, darr[i].y, darr[i].nm);
  }
  
  free(darr);                                    // free memory
  return 0;
}
