#!/bin/bash

# you need to put this where the result of ls is this:
# input/ output/ solution.cpp

# or give it a custom directory and it will run the script for that directory
# for example: bash run_scripts.sh ./q1/somewhere
for ((i=1; i<=1000; i++)); do
    ind=${i}
    #if [ ${i} -lt 10 ]; then
        #ind="0${i}"
    #fi
    dirname=`dirname $0`
    if [ "$#" -eq 1 ]; then
        dirname=$1
    fi
    inputFile="${dirname}/in/input${ind}.txt"
    outputFile="${dirname}/out/output${ind}.txt"
    script="${dirname}/solution.cpp"
    echo -e "\nrunning ${inputFile}"
    if [ -f ${inputFile} ]; then
        g++ ${script} && time ./a.out < ${inputFile} > ${outputFile}
        # python ${script} < ${inputFile} > ${outputFile}
    else
        echo "file ${inputFile} not found, ending"
        break
    fi    
done

