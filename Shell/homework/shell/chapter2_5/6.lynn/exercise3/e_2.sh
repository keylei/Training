#! /bin/bash
<<COMMENT
写一个脚本，实现以下目的：
	a.)对该目录下"1"这个文件去重复，对"2"这个文件每行前5个字符去重复，然后合并输出到"exercise3/result.txt"中
	b.)将"2"这个文件中含有"hello"的行全部转化为大写后追加输出到"exercise3/result.txt"中
COMMENT


#对该目录下"1"这个文件去重复，对"2"这个文件每行前5个字符去重复，然后合并输出到"exercise3/result.txt"中:
echo -e  "$(awk '!a[$0]++' 1)" "\n$(uniq -w 5 2)" > result.txt



#将"2"这个文件中含有"hello"的行全部转化为大写后追加输出到"exercise3/result.txt"中:
echo -e "\n\n\n\n将2中含有'hello'的行全部转化为大写后追加输出：" >> result.txt
cat 2 | grep hello | tr [:lower:] [:upper:] >> result.txt


exit 0	
