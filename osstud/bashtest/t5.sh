#!/bin/bash

a=1234

let a=a+1

echo $a

b=${a/12/AA}

echo $b

let "b = b+1"
echo $b
 
