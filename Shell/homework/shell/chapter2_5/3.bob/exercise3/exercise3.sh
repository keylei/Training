#! /bin/bash
#写一个脚本，实现一下目的:
#1.)对该目录下"1"这个文件去重复，对"2"这个文件每行前5个字符去重复，然后合并输出到"exercise3/result.txt"中
#2.)将"2"这个文件中含有"hello"的行全部转化为大写后追加输出到"exercise3/result.txt"中

#对文件１去重复输出
echo -e "对文件\"１\"去重复输出: " > result.txt | sort -u 1 >> result.txt
#对文件"2"每行前5个字符去重复输出
echo -e "\n对文件\"2\"每行前５个字符去重复输出: " >> result.txt | uniq -w 5 2 >> result.txt

#输出要求至result.txt
echo -e "\n\n将\"2\"这个文件中含有hello的行全部转化为大写后追加输出到result.txt中"　>> result.txt
#找出含有hello的行,并将其全部转化成大写输出至result.txt
grep -w hello ./2 | tr a-z A-Z >> result.txt 

exit 0

