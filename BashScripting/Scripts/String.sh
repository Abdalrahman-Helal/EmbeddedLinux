#! /bin/bash

#Strings 
str1="WelcometoJavapoint."
str2="javapoint"



# 1- String Eqauls String 
# if [ $str1 = $str2 ]
# then 
# echo "Both Strings are Equal"
# elif [ $str1 != $str2 ]
# then
# echo "Strings are different"
# else
# echo "dead code"
# fi


# 2- Greater than 
#Note [ $x \< $y ] without quotes will break because Bash sees multiple words.
#     [ $"x" \< $"y" ]
# x="Hello World"
# y="Hello"

# if [ $"x" \< $"y" ]
# then 
# echo "$x is less than $y"
# else
# echo "$x is greater than $y"
# fi 



# 3- Empty
# str="WelcometoJavapoint"

# if [ -n $str ]
# then
#     echo "String is Empty"
# else
#     echo "String is non-Empty"
# fi 

# OR
# To Check if the string length is equal to zero 
# str=""
# if [ -z $str ]
# then
#     echo "String is Empty"
# else
#     echo "String is non-empty"
# fi

# 4- Length of String 
# str="Welcome to Javapoint"
# length=${#str} #    $# get the number 
# echo "Number of '$str' is '$length'"



# str="Welcome to Javapoint"
# length=`echo $str | wc -c` 
# echo "Length of $str is $length"




# 5- Split 
str="Abdalrahman,Eslam,Helal"
IFS=',' # setting comma as demlimiter
read -ra ADDR <<<"$str" # Reading str as an array as tokens separated by IFS 

# echo ${ADDR[0]}
# len=${#str}
# echo "${len}"




# all elements of array ${ADDR[@]}
# for i in "${ADDR[@]}" # @ means accessing each element of array 
# do
# echo "$i"
# done


str="Study Smart Command with fosslinux"
substr=${str:6:13}
echo $substr