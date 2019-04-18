#!/bin/bash
# 
# Measure the performance of the matrix_timing program using the linux
# 'perf' tool which shows cache hit rates and other measures.

if [[ "$(which perf)" == "" ]]; then
    echo perf not installed;
    return 1
fi

# Set the counters that are displayed by perf
perfopts="-e cycles,"
perfopts+="instructions,"
perfopts+="branches,"
perfopts+="faults,"
perfopts+="cache-references,"
perfopts+="cache-misses,"
perfopts+="L1-dcache-loads,"
perfopts+="L1-dcache-load-misses,"
perfopts+="L1-dcache-stores,"
perfopts+="L1-dcache-store-misses,"
perfopts+="L1-dcache-prefetch-misses,"
perfopts+="L1-icache-load-misses"

gcc -Og -o matrix_timing matrix_timing.c

echo PERF OPTIONS: $perfopts

rows=8000
cols=4000 
echo RUNNING BOTH
./matrix_timing $rows $cols both
echo RUNNING ROWS
perf stat $perfopts ./matrix_timing $rows $cols row
echo RUNNING COLUMNS
perf stat $perfopts ./matrix_timing $rows $cols col
