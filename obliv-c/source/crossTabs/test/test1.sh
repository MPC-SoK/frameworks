#!/bin/bash

echo "-----------------------TEST_1: Sorting--------------------------------"

CORRECT_OUTPUT=./output1.correct.txt
OUTPUT_FILE_A=./output1.test.alice.tmp
OUTPUT_FILE_B=./output1.test.bob.tmp
ERROR_FILE_A=./error1.test.alice.tmp
ERROR_FILE_B=./error1.test.bob.tmp

make

(./testSorting.o 1234 -- input1.txt > ${OUTPUT_FILE_A} 2> ${ERROR_FILE_A} ) &
sleep 1
./testSorting.o 1234 localhost input2.txt > ${OUTPUT_FILE_B} 2> ${ERROR_FILE_B}

diff ${OUTPUT_FILE_A} ${CORRECT_OUTPUT}
diff ${OUTPUT_FILE_B} ${CORRECT_OUTPUT}
echo -n "" | diff ${ERROR_FILE_A} -
echo -n "" | diff ${ERROR_FILE_B} -

rm ${OUTPUT_FILE_A} ${OUTPUT_FILE_B} ${ERROR_FILE_A} ${ERROR_FILE_B}
