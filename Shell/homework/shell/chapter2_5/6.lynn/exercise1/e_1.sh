#! /bin/bash
<<COMMENT
写一个脚本，除了第一行是#！ /bin/bash以及最后一行是exit 0以外不许超过5行的命令实现以下目的：
	a.)找出所有后缀名为".txt"的文件（含子目录），然后将其中的内容合并输出到exercise1/result.txt中
	b.)删除exercise1目录下所有以".log"为后缀名的文件
  c.)在excercise1目录下创建一个d.txt的文件，权限为777，然后找出所有权限为777的文件并将其内容也输出到exercise1/result.txt中(备注：不得覆盖前面的输出)
COMMENT
#新建“.log”文件用于测试b.)中的删除
touch c.log 


#找出所有后缀名为".txt"的文件（含子目录），然后将其中的内容合并输出到exercise1/result.txt中
echo -e "所有后缀名为'.txt'的文件的内容:\n$(cat $(find . -name '*.txt' ! -name 'result.txt'))\n\n\n\n\n所有权限为777的文件的内容:" > result.txt


#删除exercise1目录下所有以".log"为后缀名的文件
rm *.log


#在excercise1目录下创建一个d.txt的文件，权限为777，然后找出所有权限为777的文件并将其内容也输出到exercise1/result.txt中(备注：不得覆盖前面的输出)
echo -n "$(touch d.txt)" "$(chmod 777 d.txt)" | cat $(find -type f -perm 777) >> result.txt


exit 0
