#! /bin/bash

echo "PID of this script: $$"
# echo $0
# echo $1
# echo $3
# echo $# #count
# echo $@ #list
# echo $* #string


# ecsaasdasda # this isn't valid command so $? output error  
# # echo $? # Check last command : 0 means success else error
# if [ $? -eq 0 ]
# then
# echo "Success"
# fi


# Arguments with array 
# args=("$@")
# echo "arguments to the shell" 
# echo ${args[0]} ${args[1]} ${args[2]}   



# $@ vs $*
for i in "$@"
do
echo $i
done


for i in "$*"
do
echo $i
done

