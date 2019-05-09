#!/bin/bash
# 
# create a "big" compile where there are a number of function
# definitions in different files needed by a main function. Creates
# header, each C file, and Makefile to demonstrate concepts in
# separate compilation.


limit=20
idxs=$(seq $limit)

mainname="main_func"
mainfile="main_func.c"
header="funcs.h"
makefile="Makefile"

# first part of main
cat > $mainfile <<EOF
#include <stdio.h>
#include "funcs.h"
int main(int argc, char *argv[]){
  // call various library functions
EOF

# first part of header
cat > $header <<EOF
EOF

# first part of makefile
cat > $makefile <<EOF
all : $mainname

$mainname.o : $mainname.c
	gcc -c \$<

clean : 
	rm -f *.o $mainname

EOF


# loop to build up functions in various files
for i in $idxs; do
    name=$(printf "func_%02d" "$i")
    file="${name}.c"

    # add call to main
    printf "  %s();\n" "$name" >> $mainfile

    # add func to header
    printf "void %s();\n" "$name" >> $header

    # add makefile target
    printf "%s.o : %s.c\n" "$name" "$name" >> $makefile
    printf '\tgcc -c $<\n' >> $makefile
    printf "\n" >> $makefile

    # create func C file
cat > "$file" <<EOF
#include <stdio.h>
void $name(){
  printf("Calling function $name\n");
}
EOF

done

# finish main source file
cat >> $mainfile <<EOF
  return 0;
}
EOF

# finish makefile
printf "$mainname : $mainname.o " >> $makefile
for i in $idxs; do
    file=$(printf "func_%02d.o" "$i")
    printf "$file " >> $makefile
done
printf "\n" >> $makefile
cat >> $makefile <<'EOF'
	gcc -o $@ $^
EOF


