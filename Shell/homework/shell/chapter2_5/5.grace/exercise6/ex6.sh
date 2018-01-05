#! /bin/bash
#==============================================================================================================================
# 6、在exercise6目录下写一个脚本，要实现以下目的
#	a.) 能够把执行时的参数全部改为大写输出到该目录下result.txt中
#	b.) 根据参数名创建文件，然后文件名不发生变化的情况必须要确保全部是大写
# c.) 将文件名最长的那个名称以及该名称有多少个字节追加输出到result.txt中
# d.) 最后将该脚本名称全部小写追加输出到该目录下result.txt中
#==============================================================================================================================
#将执行时的参数全部改为大写输出到该目录下result.txt中
echo "请输入字符串:" 
read string

printf "输入的字符串为:%s\n" $string > result.txt
echo -n "转为大写：" >> result.txt
echo $string | tr a-z A-Z >> result.txt

#根据参数名创建文件，然后文件名不发生变化的情况必须要确保全部是大写
echo "请输入文件名（将转为全部大写）：" 
read filename

touch "${filename^^}" 
echo "您创建的文件名是：${filename^^}" >> result.txt

#将文件名最长的那个名称以及该名称有多少个字节追加输出到result.txt中

string=""

filenames="this is a filename"
for var in $filenames
do
  if [ "${#string}" -le "${#var}" ]
    then
    string=var
  fi
done

echo "文件名最长的文件为：" ${!string} >> result.txt
echo "该名称下字节个数：" >> result.txt
echo ${!string} | wc -L >> result.txt

#最后将该脚本名称全部小写追加输出到该目录下result.txt中

echo "该脚本名称全部小写：${0,,}" >> result.txt
