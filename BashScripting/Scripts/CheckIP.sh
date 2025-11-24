#! /bin/bash

SUCCESS=" 0% packet"

for i in {1..15}
do
    result=`ping "192.168.1.${i}" -c 1 -W 1`
    # echo ${result}
    # * means everything 
    if [[ ${result} == *${SUCCESS}* ]] 
    then
        echo "192.168.1.${i} is exist"
    # else
        # echo "192.168.1.${i} is not exist"
    fi
done

