#!/bin/bash
#
# Try various -O1 options to gcc to see if any of them are individualy
# responsible for speedup in sum_range.c code.  Initial finding was
# that no single option enables speedup.

# From gcc manual
opts="-fauto-inc-dec -fbranch-count-reg -fcombine-stack-adjustments -fcompare-elim -fcprop-registers -fdce -fdefer-pop -fdelayed-branch -fdse -fforward-propagate -fguess-branch-probability -fif-conversion2 -fif-conversion -finline-functions-called-once -fipa-pure-const -fipa-profile -fipa-reference -fmerge-constants -fmove-loop-invariants -freorder-blocks -fshrink-wrap -fshrink-wrap-separate -fsplit-wide-types -fssa-backprop -fssa-phiopt -ftree-bit-ccp -ftree-ccp -ftree-ch -ftree-coalesce-vars -ftree-copy-prop -ftree-dce -ftree-dominator-opts -ftree-dse -ftree-forwprop -ftree-fre -ftree-phiprop -ftree-sink -ftree-slsr -ftree-sra -ftree-pta -ftree-ter -funit-at-a-time"

for f in $opts; do
    echo OPTION: $f
    echo gcc -Og $f sum_range.c
    gcc -Og $f sum_range.c 
    ./a.out 0 100000000
done
