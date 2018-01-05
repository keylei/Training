#! /bin/bash 
#==========================================================================================================
#  4、在exercise4目录下写一个脚本，实现对"orig.txt"和"new.txt"中不同部分输出到该目录"result.txt"中，然后用tar来实现bzip2压缩打包（注意：后缀名一定要符合通用规范）
#==========================================================================================================
printf "显示文件orig.txt和new.txt内容：\n"  > result.txt
cat -n orig.txt  >> result.txt
printf "\n" >> result.txt
cat -n new.txt >> result.txt
printf "====================================================================\n"  >> result.txt
printf "输出orig.txt和new.txt中不同部分：\n" >> result.txt
diff -yw orig.txt new.txt >> result.txt
printf "====================================================================\n"  >> result.txt
printf "查看用tar来实现bzip2压缩打包：" \n >>  result.txt
tar -cjf result.tar.bz2 result.txt       #去掉-v不显示被压缩的文件名
ls -l *.bz2 >>  result.txt
exit 0
 
