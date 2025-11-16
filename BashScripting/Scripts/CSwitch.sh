#! /bin/bash

echo "Do you know me ? "
read -p "Answer is " Answer

case $Answer in 
YES|yes|Yes|Y|y)
echo "Welcome"
;;
NO|no|No|N|n)
echo "Bye"
;;
*)
echo "Default"
esac