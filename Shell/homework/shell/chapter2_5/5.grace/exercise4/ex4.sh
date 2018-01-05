#! /bin/bash
#==============================================================================================================================
#4、在exercis4目录下写一个脚本，实现对"orig.txt"和"new.txt"中不同部分输出到该目录"result.txt"中，然后用tar来实现gzip2亚索打包（注意：后缀名一定要符合通用规范）
#==============================================================================================================================

#对"orig.txt"和"new.txt"中不同部分输出到该目录"result.txt"中
printf ""orig.txt"和"new.txt"中不同部分:\n" > result.txt
grep -vf ./new.txt ./orig.txt >> result.txt
grep -vf ./orig.txt ./new.txt >> result.txt

#用tar来实现gzip2亚索打包
tar -cjvf result.txt.tar.bz2 result.txt
