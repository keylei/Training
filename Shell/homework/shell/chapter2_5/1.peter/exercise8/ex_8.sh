#! /bin/bash

#==============================================================================
#8、在exercise8目录下写一个脚本，要实现以下目的：
#	a.)输出该脚本所在父Shell的进程号到该目录下result.txt
# 	b.)追加输出该脚本子Shell进程号到该目录下result.txt
# 	c.)在/proc下找出与父Shell及子Shell进程相关的目录下所有文件，将文件后缀名去
#	   掉后逐行追加输出到该目录下result.txt(要求：这些需要追加输出到result.txt
#	   的名称要
#   求先在脚本中赋值给一个数组，然后通过数组循环再追加输出到result.txt)
#==============================================================================

> result.txt	#创建result.txt文件

echo -e "该脚本父shell进程号:\t$PPID" >> result.txt	#输出脚本父shell进程号
echo -e "该脚本shell进程号:\t$$" >> result.txt		#输出脚本shell进程号

declare -a arrayname				#声明数组arrayname
echo "输出父shell进程在/proc下的相关文件:" >> result.txt
arrayname=($(find /proc/$PPID/ *))		#找出父shell在/proc下的相关文件
for i in ${arrayname[@]};do
	echo ${i%.*} >> result.txt		#去除后缀名输出到result.txt
done


echo "输出子shell进程在/proc下的相关文件:" >> result.txt
arrayname=($(find /proc/$$/ *))			#找出子shell在/proc下的相关文件
for i in ${arrayname[@]};do
	echo ${i%.*} >> result.txt		#去除后缀名输出到result.txt
done

exit 0

