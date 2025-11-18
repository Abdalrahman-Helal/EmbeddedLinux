#! /bin/bash

#Define Array 
# declare -a ARRAY_NAME=( "Java" "Pyhton" "HTML" "CSS" "JavaScript" ) 
ARRAY_NAME2=("Java" "Python" "HTML" "CSS" 3 ) #both are correct ways to define array , NOTE : u can add Numerical Value in array 

# overwrite value in array 
# ARRAY_NAME2[0]="cpp"

#Indexing 
# ${ARRAY_NAME[index]} # Get Value 
# ${ARRAY_NAME[@]} # Get all elements
# ${#ARRAY_NAME[@]} # Length

# echo ${ARRAY_NAME[0]}
# echo " " ${ARRAY_NAME2[@]}
# echo "The Array Contains ${ARRAY_NAME[@]} Elements"


#Delete any variable or element in array 
# x=10
# unset x 
# unset ARRAY_NAME2[2] # this index becomes empty after unset
# echo ${ARRAY_NAME2[@]}
# echo "The Array Contains ${ARRAY_NAME2[@]} Elements"
# echo ${ARRAY_NAME2[2]}  # empty value in this index 




# Slicing 
# SLICED_ARRAY=("${ARRAY_NAME2[@]:1:3}") # End is included not like python
# echo "The Sliced Array :" ${SLICED_ARRAY[@]}
# echo "Index 1 in array :" ${SLICED_ARRAY[1]}



#Remember in String
# str="Abdalrahman Eslam Mohamed Helal"
# echo ${str:12:5}  #:Start:No Of Character to print (Not End)



# For Loop to Iterate over Element in Array
# for i in "${ARRAY_NAME2[@]}"
# do 
# echo $
# done



# what if i want to get index value 
for i in "${!ARRAY_NAME2[@]}"
do
echo "$i -  ${ARRAY_NAME2[$i]} "
done