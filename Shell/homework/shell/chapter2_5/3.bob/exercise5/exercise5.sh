#! /bin/bash
#在exercise5目录下写一个脚本，对"name"和"age"这两个文本合并（name在前，age在后）然后按数值的方式对第2列排序输出到该目录下"result.txt"中
#新建一个result.txt文件
> result.txt
#将"name"和"age"两个文件先合并，并按第二列排序
echo -e "合并\"name\"和\"age\"\nname  age" >> result.txt
paste -d ':' name age | sort -k 2 >> result.txt

exit 0


