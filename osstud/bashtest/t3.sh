#!/bin/bash

a=12+5

echo a
echo $a
echo "$a"
echo '$a'

let b=12+5

echo
echo b
echo $b
echo "$b"
echo '$b'

echo
for a in 8 9 10
do
   echo -n "$a "
done
echo
echo

echo -n c=
read c
echo "c=$c"

