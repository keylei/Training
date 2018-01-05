#! /bin/bash
#  exercise 2


 var=$PATH

 echo -n "变量a的值: "; read a 

 echo -n "变量b的值: "; read b

 let c=$a+$b
 
 printf "环境PATH是\"%s\"\n变量a的值: %s\n变量b的值: %s\na+b的值: %s\n" $var $a $b $c >> result.txt
 
 age=28

 name=bob

 income=1000

 printf "姓名: %s\n年龄: %d\n收入:%6.2f\n" $name $age $income >> result.txt







