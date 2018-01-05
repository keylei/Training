#! /bin/bash

#==============================================================================
#6、在exercise6目录下写一个脚本，要实现以下目的
#	a.) 能够把执行时的参数全部改为大写输出到该目录下result.txt中
#	b.) 根据参数名创建文件，然后文件名不发生变化的情况必须要确保全部是大写
# 	c.) 将文件名最长的那个名称以及该名称有多少个字节追加输出到result.txt中
#	d.) 最后将该脚本名称全部小写追加输出到该目录下result.txt中
#==============================================================================

> result.txt		#创建result.txt文件

#输入参数,并将参数改为大写放入result.txt中
echo -e "请输入参数,以空格分割参数:"; read filelist
echo "大写的参数名称:" >> result.txt
echo ${filelist^^} >> result.txt


#按照参数创建文件,名称是大写
echo -e "\n按照参数创建文件,且文件名是大写.\n" >> result.txt
for filename in ${filelist^^};do
touch $filename 
done


#用for循环选出文件名最长的文件
long=" "
for var in ${filelist^^}
do
	if [ ${#long} -le ${#var} ]
		then 
			long="$var"
	fi
done 

echo "最长的文件名是:$long" >> result.txt
echo "最长的文件名大小是:$(echo $long | wc -c)字节" >> result.txt


echo -e "\n该脚本小写名称:">>result.txt	#将该脚本名称小写输出到result.txt中
scriptname=${0##*/}			#脚本名称去除路径
echo "${scriptname,,}" >> result.txt	#脚本名称小写

exit 0

