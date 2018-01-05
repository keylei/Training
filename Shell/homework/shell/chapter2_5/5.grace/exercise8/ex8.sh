#! /bin/bash
#=============================================================================================================================
# 8、在exercise8目录下写一个脚本，要实现以下目的：
#	a.)输出该脚本所在父Shell的进程号到该目录下result.txt
# b.)追加输出该脚本子Shell进程号到该目录下result.txt
# c.)在/proc下找出与父Shell及子Shell进程相关的目录下所有文件，将文件后缀名去掉后逐行追加输出到该目录下result.txt(要求：这些需要追加输出到result.txt的名称要求先在脚本中赋值给一个数组，然后通过数组循环再追加输出到result.txt)
#============================================================================================================================

#输出该脚本所在父Shell的进程号到该目录下result.txt
echo "PPID of this script: $PPID" > result.txt

#追加输出该脚本子Shell进程号到该目录下result.txt
echo "PID of this script: $$" >> result.txt

#在/proc下找出与父Shell及子Shell进程相关的目录下所有文件，将文件后缀名去掉后逐行追加输出到该目录result.txt(要求：这些需要追加输出到result.txt的名称要求先在脚本中赋值给一个数组，然后通过数组循环再追加输出到result.txt)
printf "父shell和子shell下的文件去后缀名结果为：\n" >> result.txt

declare -a a                                       #定义数组
while read i;
do
  a=("${a[@]}" "$i")
done < <(find "/proc/$$" "/proc/$PPID" -type f)  

echo ${a[@]}
for var in ${a[@]} 
do
  echo ${var##*.} >> result.txt                   #去文件后缀名并输入到文件中
done

exit 0




