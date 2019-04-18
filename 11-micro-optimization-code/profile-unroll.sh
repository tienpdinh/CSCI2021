#!/bin/bash

# remove old files
rm -f gmon.out unroll

# Compile
# -pg : instrument code for profiling
# -no-pie : bug fix for new-ish gcc's
gcc -pg -no-pie -g -Og -o unroll unroll.c

# show source and executable
ls

# run program
./unroll 1000000000

# show that gmon.out has been produced
ls

# show type of file for gmon.out
file gmon.out

# examine profile for unroll
gprof -b unroll
