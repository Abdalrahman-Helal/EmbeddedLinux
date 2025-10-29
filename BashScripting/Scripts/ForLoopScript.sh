#! /bin/bash

# set -x  
# var = "Helal"
# for i in 1 2 3 4 5 6
# do 
# echo ${i}
# done
# set +x
# echo "Thanks You"




# for i in {1..10}
# do
# echo "The Number is ${i}"
# done



# learn="Start Learning From Javapoint"
# for i in $learn
# do
# echo $i
# done
 



# x=`ls`
# for i in ${x}
# do
# echo "The File Name is ${i}"
# done



files=`ls test`
for i in ${files}
do
    echo "The Content of file ${i} is :"
    cat "./test/${i}"
    echo
done
 
echo "Thank You"