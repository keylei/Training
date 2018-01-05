#! /bin/bash

#==============================================================================
#5、在exercise5目录下写一个脚本，对"name"和"age"这两个文本合并（name在前，age在后）
#   然后按数值的方式对第2列排序输出到该目录下"result.txt"中
#==============================================================================

> result.txt		#创建result.txt

#合并"name"和"age"文件内容,按数值排序
echo -en "合并\"name\"和\"age\"文件,按年龄排序:\n" >> result.txt
paste name age | sort -k 2  >> result.txt


exit 0

