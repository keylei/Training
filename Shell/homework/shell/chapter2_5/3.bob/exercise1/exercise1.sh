#! /bin/bash
#在exercise1目录下写一个脚本，除了第一行是#！ /bin/bash以及最后一行是exit 0以外不许超过5行的命令实现以下目的：
#a.)找出所有后缀名为".txt"的文件（含子目录），然后将其中的内容合并输出到exercise1/result.txt中
#b.)删除exercise1目录下所有以".log"为后缀名的文件
#c.)在excercise1目录下创建一个d.txt的文件，权限为777，然后找出所有权限为777的文件并将其内容也输出到exercise1/result.txt中(备注：不得覆盖前面的输出)

#找出目录下后缀名为".txt"的文件（含子目录），然后将其中的内容合并输出到exercise1/result.txt中
echo "将所有后缀为.txt的文件内容输出至result.txt文件中" > ./result.txt | find ./ -type f -name "*.txt" -a ! -name "result.txt" -exec echo "文件的路径及内容: " {} \; -exec cat -n {} \; >> ./result.txt

#删除exercise1目录下所有以".log"为后缀名的文件
echo -e "\n\n删除该目录下所有*.log文件已完成" >> result.txt | find ./ -type f -name "*.log" -exec rm -f {} \;

#在excercise1目录下创建一个d.txt的文件，权限为777，然后找出所有权限为777的文件并将其内容也输出到exercise1/result.txt中(备注：不得覆盖前面的输出)
echo -e "\n\n创建一个权限为777的d.txt的文件，并将该目录内所有权限为777的文件内容输出至result.txt中" >> result.txt | touch d.txt | chmod 777 d.txt
find ./ -type f -perm 777 -exec cat {} \;>> result.txt

exit 0

	
