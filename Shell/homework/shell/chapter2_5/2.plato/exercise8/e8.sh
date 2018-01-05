#! /bin/bash
#============================================================================================================================================================================================
# 8、在exercise8目录下写一个脚本，要实现以下目的：
# 	a.)输出该脚本所在父Shell的进程号到该目录下result.txt
#  	b.)追加输出该脚本子Shell进程号到该目录下result.txt
#  	c.)在/proc下找出与父Shell及子Shell进程相关的目录下所有文件，将文件后缀名去掉后逐行追加输出到该目录下result.txt
#	  (要求：这些需要追加输出到result.txt的名称要求先在脚本中赋值给一个数组，然后通过数组循环再追加输出到result.txt)
#============================================================================================================================================================================================

# a.)输出父Shell进程号
	echo "该脚本所在父Shell的进程号为：$PPID" > result.txt

# b.)输出子Shell进程号
	echo "该脚本子Shell的进程为：$$" >> result.txt

# c.)输出父Shell及子Shell进程目录下文件
echo '' >> result.txt

	echo "父Shell进程目录下文件：" >> result.txt
	arr1=($(find /proc/$PPID -type f))		#间接声明数组arr1
	for var1 in ${arr1[*]}					#循环输出
	do
		echo ${var1%.*} >> result.txt		#去掉后缀名输出
	done 

echo '' >> result.txt
  
	echo "子Shell进程目录下文件：" >> result.txt
	arr2=($(find /proc/$$ -type f))			#间接声明数组arr2
	for var2 in ${arr2[*]}					#循环输出
	do
		echo ${var2%.*} >> result.txt		#去掉后缀名输出
	done 

exit 0
