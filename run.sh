#!/bin/bash 

#$1 corresponds to the name of the executable
#2 corresponds to the path to the images directory
prog=$1
images=$2
patterns=$3

#make a copy directory for minipulate files placeholder
mkdir $patterns/cpyDirectory
#traverse the files in the pattern directory
for file in $patterns/*.pat; 
do
    while IFS= read -r line
    do
        echo "${line%$'\r'}"
    done < $file > $patterns/cpyDirectory/"$(basename -- $file.temp)"
    mv $patterns/cpyDirectory/"$(basename -- $file.temp)" $patterns/"$(basename -- $file)"
done;
#remove copy directory
rm -fR $patterns/cpyDirectory
#run the program with each pattern and image file as arguments
for FILE in $patterns/*.pat;
do
    for file in $images/*.img;
    do
        ./$prog $FILE $file
    done
done;
