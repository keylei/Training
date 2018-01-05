#! /bin/bash
#题目要求
#a.)输出该脚本所在父Shell的进程号到该目录下result.txt
#b.)追加输出该脚本子Shell进程号到该目录下result.txt
#c.)在/proc下找出与父Shell及子Shell进程相关的目录下所有文件，将文件后缀名去掉后逐行追加输出到该目录下result.txt(要求：这些需要追加输出到result.txt的名称要求先在脚本中赋值给一个数组，然后通过数组循环再追加输出到result.txt)

echo "1.输出该脚本所在的父Shell的进程号： $PPID" > result.txt

echo -e "\n\n2.输出该脚本的进程号： $PPID" >> result.txt

#申明一个数组变量
declare -a arrayfile1 arrayfile2
#将数组变量赋值
arrayfile1=$(find /proc/$PPID/ *)
arrayfile2=$(find /proc/$$/ *)
#输出提示
echo -e "\n\n3.输出父shell进程相关目录下的所有文件" >> result.txt
#将变量逐行输出至result.txt
for  var in ${arrayfile1[*]};
do
   echo ${var%.*} >> result.txt
done 
#输出提示
echo -e "\n输出子shell进程相关目录下的所有文件" >> result.txt
#将变量逐行输出至result.tx
for  var in ${arrayfile2[*]};
do
   echo ${var%.*} >> result.txt
done   

exit 0
  













