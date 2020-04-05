#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Input files
INPUT_GLOB=input/peak*.in

# Where to find for `lab_extra` executable
printf "${GREEN}¡Running lab_extra!${NC}\n\n"

# Count files to test
N_FILES=$(ls ${INPUT_GLOB} | wc -l | xargs)
printf "Total number of files to test: ${N_FILES}\n\n"

# Test all peak files
i=1;
for filename in ${INPUT_GLOB}; do
    printf "[${i}/${N_FILES}] Finding peak for $filename... "
    expected_result=$(tail -1 $filename)
    retval=$(./lab_extra "$filename" | awk 'END {print $NF}')
    if [ $retval -ne $expected_result ];
    then
        printf "${RED}ERROR${NC} --> ";
        printf "Expected result is ${expected_result} but result was ${retval}. \n"
        exit $retval;
    else
        printf "${GREEN}SUCCESS${NC}\n";
    fi
    ((i++))
done

exit 0;
