#! /bin/bash
#在exercise6目录下写一个脚本，要实现以下目的
#a.) 能够把执行时的参数全部改为大写输出到该目录下result.txt中
#b.) 根据参数名创建文件，然后文件名不发生变化的情况必须要确保全部是大写
#c.) 将文件名最长的那个名称以及该名称有多少个字节追加输出到result.txt中
#d.) 最后讲该脚本名称全部小写追加输出到该目录下result.txt中

#将执行文件中参数全部大写输出值result.txt中
echo -e "将执行文件中参数全部大写输出：" > result.txt
#输入要创建的文件名提示
echo "请输入要创建的文件名: "  
#输入要创建的文件名
read dir 
#找出输入的文件
for file in $dir; do  touch ${file^^}; done
#将文件名全部大写输出
echo $dir | tr a-z A-Z >> result.txt


#定义变量a，并将其赋值为0
declare -i a 
a=0;
#找出最长的文件名及文件名的长度
for file in $dir
do
  if [ $a -le ${#file} ]; 
   then a=${#file};  
        m=$file
   fi
done
#输出最长文件名的名称
echo -e "\n\n最长文件名称为: $m" >> result.txt
#输出最长文件名的字符数
echo -e "\n最长文件名的字符数为: $a" >> result.txt


#输入题目要求
echo -e "\n\n将脚本名全部小写输出至result.txt" >> result.txt
#将脚本名字全部改成小写,输出至result.txt中
var=${0,,}
echo ${var##*/} >> result.txt

exit 0












