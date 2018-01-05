#! /bin/bash
#  exercise 3


 var="peter is a good student"
 
 for word in $var; do   echo "$word" >> ref.txt; done

 var2=peterlovecosplay

 var3=123
	
 printf "%9.9s%s\n" $var2 $var3 >> ref.txt

 dir="/home/bob/"

 printf "the path : ${dir}\n" >> ref.txt

 a="i love china"
 
 b="/etc/var/"

 c=$(pwd)

 printf "单引号输出:　'$a'\t'$b'\t'$c'\n" >> ref.txt

 printf "双引号输出:　\"$a\"\t\"$b\"\t\"$c\"\n" >> ref.txt
 
 printf "大括号输出:　${a}\t${b}\t${c}\n" >> ref.txt 

# for x in '$a'; do echo  $x >> ref.txt; done
 
# echo '$b' >> ref.txt

# for y in "$a"; do echo  $y >> ref.txt; done
 
# echo "$b" >> ref.txt

# for y in {$a}; do echo  $y >> ref.txt; done
 
# echo ${b} >> ref.txt






