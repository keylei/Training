#! /bin/bash

#==============================================================================
#1、在exercise1目录下写一个脚本，除了第一行是#！ /bin/bash以及最后一行是exit 0以外
#   不许超过5行的命令实现以下目的：
#	a.)找出所有后缀名为".txt"的文件（含子目录），然后将其中的内容合并输出到
#	   exercise1/result.txt中
#	b.)删除exercise1目录下所有以".log"为后缀名的文件
#  	c.)在excercise1目录下创建一个d.txt的文件，权限为777.然后找出所有权限为777
#	   的文件并将其内容也输出到exercise1/result.txt中(备注:不得覆盖前面的输出)
#==============================================================================

#找出所有后缀名为".txt"的文件(含子目录),然后将其中的内容合并输出到/exercise1/result.txt中.
echo "显示\".txt\"为后缀名的文件内容:" > result.txt 
find . -name "*.txt" -a ! -name "result.txt"  -exec cat {} \; >> result.txt


#删除exercise1目录下所有以".log"为后缀的文件
find . -name "*.log" -exec rm -r {} \; && echo -e "\n成功删除\".log\"为后缀名的文件:\n" >> result.txt


#在exercise1的目录下创建名为d.txt权限为777的文件
touch d.txt | chmod 777 d.txt && echo -en "\n成功创建文件\" d.txt\",并将权限改为777.\n" >> result.txt 
#找出所以权限为777的文件并将其内容输出到exercise1/result.txt中.
echo -en "\n显示权限为777的文件内容:\n" >> result.txt 
find . -perm 0777 -exec cat {} \; >> result.txt

exit 0


