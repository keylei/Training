#! /bin/bash
z=$PATH
printf "环境PATH是：$z\n" >> result.txt

a=3
b=7
let c=$a+$b
printf " a: %c \n b: %c \n a+b: %1.2f \n" $a $b $c >> result.txt

name=yy
age=12
income=56789.1234
printf "姓名：$name	年龄：$age	收入： %1.2f \n" $income >> result.txt
