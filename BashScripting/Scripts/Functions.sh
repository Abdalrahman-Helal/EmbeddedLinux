#! /bin/bash


# function test3()
# {
#     echo "Welcome"
# }
# test3


DisplayHello()
{
    echo "Hello Function"
}
DisplayHello


DisplayHelloArgument()
{
    echo $0 $1 $2 $3 $4
}
# DisplayHelloArgument hello from abdalrhman helal
DisplayHelloArgument $1 $2 abdalrahman helal  # To send Parameters in terminal ex: ./Bash.sh Hi From
                                              # Output : Hi From abdalrahman Helal




add()
{
    sum=$(($1 + $2))
    return $sum
}
a=10
b=20

add $a $b
result=$? #return of last command saved in $? by default
echo "$result"