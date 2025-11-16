#! /bin/bash 
x=8 
y=2
z= expr 1 + 2 
echo $z

let sum=3+10
echo $sum

((x++))
echo $x
echo "x=8 , y=2"
echo "Addition of x & y"
echo $(($x + $y)) # note : you should add $ before the ()
echo "Subtraction of x & y"
echo $(($x - $y))
echo "Multiplication of x & y"
echo $(($x * $y))
echo "Division of x & y"
echo $(($x / $y))
echo "Modular of x & y"
echo $(($x % $y))
echo "Exponentiation of x & y"
echo $(($x ** $y))

echo "Incrementing x by 5 ,then x= "
((x +=5))
echo $x

echo "Multiply of x by 5 ,then x= "
((x *=5))
echo $x

echo "Dividing of x by 5 ,then x= "
((x /=5))
echo $x

echo "Reminder of Dividing x by 5 ,then x= "
((x %=5))
echo $x 