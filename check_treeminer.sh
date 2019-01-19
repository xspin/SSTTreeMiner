#!/bin/bash

test_files="
test_out3.data
test_out2.data
test_out1.data
"

for fn in ${test_files}; do
    echo -e "\nchecking ..." $fn
    f1="treeminer/${fn}"
    f2="TreeMiner-wulangbnu/${fn}"
    c1=(`md5sum ${f1}`)
    c2=(`md5sum ${f2}`)
    if [ "${c1[0]}" = "${c2[0]}" ]; then
        echo "  Pass"
    else
        echo "  Not match"
        echo "  " ${c1[0]}
        echo "  " ${c2[0]}
    fi;
    cmp --silent $f1 $f2 || echo "  Files are different"
done

#echo ${test_files}