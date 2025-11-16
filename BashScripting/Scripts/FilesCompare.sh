#! /bin/bash

if [ -z $1 -o -z $2 ] # Check if 1st file is Zero OR 2nd file is Zero 
then 
    echo "Usage FilesCompare <file1> <file2>"
exit 0 
fi

file1=`md5sum $1`
file2=`md5sum $2`
echo "File 1 is $file1"
echo "File 2 is $file2"


if [ "$file1" = "$file2" ] 
then 
    echo "these files are similar"
else    
    echo "these files are different"
fi
