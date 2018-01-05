#! /bin/bash

#==============================================================================
#4、在exercis4目录下写一个脚本，实现对"orig.txt"和"new.txt"中不同部分输出到该目录
#   "result.txt"中，然后用tar来实现bzip2压缩打包（注意：后缀名一定要符合通用规范）
#==============================================================================

> result.txt		#创建result.txt文件

#对比"orig.txt和new.txt的不同,并输出到result.txt
echo -en "\"new.txt\"与\"orig.txt\"不同的行:\n" >> result.txt
diff -y orig.txt new.txt | grep -w "|" >> result.txt

echo -en "\n\"new.txt\"比\"orig.txt\"多的行:\n" >> result.txt
diff -y orig.txt new.txt | grep -w ">" >> result.txt

echo -en "\n\"new.txt\"比\"orig.txt\"少的行:\n" >> result.txt
diff -y orig.txt new.txt | grep -w "<" >> result.txt

#用tar命令实现bzip2压缩打包result文件
tar -cjvf result.txt.bz result.txt 

exit 0

