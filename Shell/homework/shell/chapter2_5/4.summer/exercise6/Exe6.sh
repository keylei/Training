#! /bin/bash 
#==========================================================================================================
#  6、在exercise6目录下写一个脚本，要实现以下目的
#  	a.) 能够把执行时的参数全部改为大写输出到该目录下result.txt中
# 	b.) 根据参数名创建文件，然后文件名不发生变化的情况必须要确保全部是大写
#   c.) 将文件名最长的那个名称以及该名称有多少个字节追加输出到result.txt中
#   d.) 最后将该脚本名称全部小写追加输出到该目录下result.txt中
#==========================================================================================================
echo "把执行时的参数全部改为大写输出到该目录下result.txt中：" > result.txt
# 将参数更改为大写,将其输入到文件中并创建相应大写文件
for var in $*
do
   echo ${var^^} >> result.txt
   touch ${var^^}
done
printf "\n"   >> result.txt
printf "====================================================================\n"  >> result.txt
echo " 根据参数名创建文件，然后文件名不发生变化的情况必须要确保全部是大写:" >> result.txt
echo " 查看exercise6文件夹下的文件和文件夹:" >> result.txt
ls -l ./ >> result.txt
printf "\n"  >> result.txt
printf "====================================================================\n"  >> result.txt

# 查找最长文件名称，赋值给maxfilename
maxfilename=""
for tmp in $*
do
	if [ ${#tmp} -gt ${#maxfilename} ]
  then
  		maxfilename=$tmp
  fi
done
echo " 文件名最长的那个名称:" $maxfilename >> result.txt


printf " 最长文件名的字节数:" >> result.txt
echo -e $maxfilename | wc -c >> result.txt
printf "\n"  >> result.txt
printf "====================================================================\n"  >> result.txt

scriptpath=$0  #获取脚本名称
echo -e "将该脚本名称去掉路径:" ${scriptpath##*/} >> result.txt
scriptname=${scriptpath##*/}
echo -e "将该脚本名称去掉路径后全部小写追加输出到该目录下result.txt中:" "${scriptname,,}" >> result.txt
exit 0
