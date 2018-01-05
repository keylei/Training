#! /bin/bash
<<COMMENT
在exercise8目录下写一个脚本，要实现以下目的：
	a.)输出该脚本所在父Shell的进程号到该目录下result.txt
  b.)追加输出该脚本子Shell进程号到该目录下result.txt
  c.)在/proc下找出与父Shell及子Shell进程相关的目录下所有文件，将文件后缀名去掉后逐行追加输出到该目录下result.txt(要求：这些需要追加输出到result.txt的名称要求先在脚本中赋值给一个数组，然后通过数组循环再追加输出到result.txt)
COMMENT

#输出该脚本所在父Shell的进程号到该目录下result.txt
	echo "父shell进程号：$PPID" > result.txt


#追加输出该脚本子Shell进程号到该目录下result.txt
	echo "子shell进程号：$$" >> result.txt


#在/proc下找出与父Shell及子Shell进程相关的目录下所有文件，将文件后缀名去掉后逐行追加输出到该目录下result.txt
#父shell：
	echo -e "\n父shell文件：" >> result.txt
	ARRAYNAME[1]=f_file_name
	f_file_name=$(find /proc/$PPID -type f)
	for temp in $f_file_name
		do
		echo ${temp%.*} >> result.txt
		done

#子shell：
	echo -e "\n子shell文件：" >> result.txt
	ARRAYNAME[1]=s_file_name
	s_file_name=$(find /proc/$$ -type f)
	for temp in $s_file_name
		do
		echo ${temp%.*} >> result.txt
		done

exit 0
