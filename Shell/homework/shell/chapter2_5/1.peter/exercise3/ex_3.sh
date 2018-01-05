#! /bin/bash

#==============================================================================
#3、在exercise3目录下写一个脚本，实现以下目的：
#	a.)对该目录下"1"这个文件去重复，对"2"这个文件每行前5个字符去重复，然后合并
#	   输出到"exercise3/result.txt"中
#	b.)将"2"这个文件中含有"hello"的行全部转化为大写后追加输出到
#	   "exercise3/result.txt"中
#==============================================================================

> result.txt		#创建result.txt文件

#删除文件1中的重复行与文件2中前5列重复的行,合并输出到result.txt
echo "删除文件1中的重复行与文件2中前5列重复的行:" >> result.txt
sort -u 1 >> result.txt
uniq -w 5 2 >> result.txt

#将文件2中含有hello的行转化为大写,追加输出到result.txt
echo -en "\n将文件2中含有hello的行转化为大写:\n" >> result.txt
grep -w "hello" 2 | tr a-z A-Z >> result.txt
grep -v "hello" 2 >> result.txt

exit 0
