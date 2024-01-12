#!/bin/sh


read -p  "choose the dimension of the picture (must be over 100) " int1
read -p  "choose the number of point that will be appeared " int2
read -p  "choose the  significative number (between 1 and 5) " int3

python3 ./bin/draw2.py "$int1" "$int2" "$int3" 




