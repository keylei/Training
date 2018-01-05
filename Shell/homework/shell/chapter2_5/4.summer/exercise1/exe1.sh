#! /bin/bash 
#==========================================================================================================
#    1、在exercise1目录下写一个脚本，除了第一行是#！ /bin/bash以及最后一行是exit 0以外不许超过5行的命令实现以下目的：
#     a.)找出所有后缀名为".txt"的文件（含子目录），然后将其中的内容合并输出到exercise1/result.txt中
#     b.)删除exercise1目录下所有以".log"为后缀名的文件
#     c.)在excercise1目录下创建一个d.txt的文件，权限为777，然后找出所有权限为777的文件并将其内容也输出到  exercise1/result.txt中(备注：不得覆盖前面的输出)
#==========================================================================================================
printf "找出后缀名为".txt"的文件（含子目录）,然后输出到result.txt中: \n" > ./result.txt
find ./ -type f -name "*.txt" ! -name "result.txt" -exec cat {}  >> ./result.txt \;
find ./ -type f -name "*.log" -exec rm -f {} \;
printf "已经删除exercise1目录下所有以".log"为后缀名的文件\n" >> ./result.txt
touch c.log 
echo "$(touch d.txt)" "$(chmod 777 d.txt)"
printf "找到所有权限为777的文件并输出到result.txt中 \n" >> ./result.txt
find ./ -type f -perm 777 -exec cat {} >> ./result.txt \; 
exit 0
