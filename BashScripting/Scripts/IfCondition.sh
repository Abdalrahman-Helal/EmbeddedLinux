#! /bin/bash


#Test String
# test "Helal" = "Helal" && echo true
# test "Helal" = "Ahmed" && echo true || echo False


#Test Integer
# test 001 = 1 && echo Integer || echo String  # it consisders it as string not integer 
# test 001 -eq 1 && echo Integer || echo String


#if condition

# if [ 2 -eq 1 ]
# then 
# echo "the value is 1"
# else
# echo "the value is not 1"
# fi


# read -p "Enter String " str
# # -z means string is Zero
# if [ -z $str ]
# then
# echo "Empty"
# else
# echo "the string is ${str}"
# fi


# read -p "Enter Number : " number
# if [ $number -lt 125 ]
# then 
#     echo "Value is less than 125"
# elif [ $number -lt 200 ] 
# then
#     echo "the value is between 125 and 200"
# else 
#     echo "valuie is greater tha 200"
# fi 



# read -p "variable x " x
# test -z $x && echo "Empty"



# test -f "./tessst.sh" && echo "File Exist" || echo "File Doesn't Exist"

# if [ -f "./test.sh" ]
# then
#     echo "File Exist"
# else
#     echo "File Doesn't Exist"
# fi



#! /bin/bash

if [ 1 -eq 1  -a  5 -gt 4 ]
then 
echo "#rule 1"
fi 

if [ 1 -eq 1 ] && [ 5 -gt 4 ]
then 
echo "#rule 2"
fi 

if [[ 1 -eq 1  &&  5 -gt 4 ]]
then 
echo "#rule 3"
fi 


# C Style 
if((001 == 1))
then 
echo "#rule 4"
fi


x=0
if((++x))
then
echo "#rule 5"
fi

x=0
if((x++))
then
echo "#rule 6"
else
echo "#Invalid 6"
fi


<<Comment
Multiline Comment
Multiline Comment
Multiline Comment
Comment
