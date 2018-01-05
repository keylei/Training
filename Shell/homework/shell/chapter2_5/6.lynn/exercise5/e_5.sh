#! /bin/bash
<<COMMENT
在exercise5目录下写一个脚本，对"name"和"age"这两个文本合并（name在前，age在后）然后按数值的方式对第2列排序输出到该目录下"result.txt"中
COMMENT

paste -d ";" name age | sort -t ';' -k 2 -n > result.txt

exit 0
