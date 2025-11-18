#! /bin/bash


#Select 

# select name in Abdalrahman Eslam Helal 
# do 
#     echo $name
# done


#break 
# select name in Abdalrahman Eslam Helal
# do  
#     case ${name} in 
#     Helal)
#         echo "Hello ${name}"
#     ;;
#     *)
#     break
#     ;;
#     esac
# done



#Global Var 

# name="Ahmed Mohamed"

# DisplayGlobal()
# {
#     name="Abdalrahman Helal"
#     echo "Hello Function ${name}"
# }

# echo "Before ${name}"
# DisplayGlobal
# echo "after ${name}"



# DisplayLocal()
# {
#     local name="Abdalrahman Helal"
#     echo "Hello Function ${name}"
# }

# echo "Before ${name}"
# DisplayLocal
# echo "after ${name}"



# readonly
# readonly x=12
# or 
# x=10
# readonly x 
# x=12 #error

# echo $x




#readonly works with functions
# function print()
# {
#     echo hi 
# }
# print

# readonly -f print

# function print()
# {
#     echo Welcome 
# }



# Shift 

# total number of command-line arguments
echo "Total Arguments pass are : $#"


# $* is used to show command line arguments
echo "The Arguments are : $*"

echo "The First Argument is : $1"
shift 2

echo "The First Argument after shift 2 is  : $1"
shift # note u can't use shift -1 

echo "The First Argument after shift is  : $1"














