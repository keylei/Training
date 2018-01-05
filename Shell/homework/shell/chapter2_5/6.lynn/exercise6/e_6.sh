#! /bin/bash
<<COMMENT
写一个脚本，要实现以下目的
	a.) 能够把执行时的参数全部改为大写输出到该目录下result.txt中
	b.) 根据参数名创建文件，然后文件名不发生变化的情况必须要确保全部是大写
  c.) 将文件名最长的那个名称以及该名称有多少个字节追加输出到result.txt中
  d.) 最后讲该脚本名称全部小写追加输出到该目录下result.txt中
COMMENT

#把执行时的参数全部改为大写输出到该目录下result.txt中
	echo -e "所有参数的大写：\n${*^^}" > result.txt




#根据参数名创建文件，然后文件名不发生变化的情况必须要确保全部是大写
	touch "${*^^}"



#将文件名最长的那个名称以及该名称有多少个字节追加输出到result.txt中
	max=""
	for string in ${*^^}
	do
		if [ "${#max}" -le "${#string}" ] 
			then
			max=string
		fi
	done

	echo -e -n "最长文件名字节数 (其中包括一个为字符串结束标志字符) :\t" >> result.txt
	echo -e "${!max}" | wc -c >> result.txt
	echo -e "最长文件名名字：${!max}" >> result.txt

#最后将该脚本名称全部小写追加输出到该目录下result.txt中
	file=${0##*/}
	echo "该脚本全小写名称：${file,,}" >> result.txt


exit 0
