#! /bin/bash 
#==========================================================================================================
#   3、在exercise3目录下写一个脚本，实现以下目的：
#	  a.)对该目录下"1"这个文件去重复，对"2"这个文件每行前5个字符去重复，然后合并输出到"exercise3/result.txt"中
# 	b.)将"2"这个文件中含有"hello"的行全部转化为大写后追加输出到"exercise3/result.txt"中
#==========================================================================================================
echo "列出文件1的内容：" > result.txt
cat ./1 >> result.txt
printf "\n" >> result.txt
printf "====================================================================\n"  >> result.txt
echo "列出文件2的内容：" >> result.txt
cat ./2 >> result.txt
printf "\n" >> result.txt
printf "====================================================================\n"  >> result.txt
echo "对文件1去重复,文件2每行前5个字符去重复,然后合并输出到result.txt"  >> result.txt
echo -e "$(sort -u ./1)" "\n$(uniq -w 5 ./2)" >> result.txt
printf "\n" >> result.txt
printf "====================================================================\n"  >> result.txt
echo "将文件2中含有"hello"的行全部转化为大写:"  >> result.txt
grep -w hello 2 | tr a-z A-Z >> result.txt
gedit  result.txt
exit 0
