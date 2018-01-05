#! /bin/bash
<<COMMENT
在exercis4目录下写一个脚本，实现对"orig.txt"和"new.txt"中不同部分输出到该目录"result.txt"中，然后用tar来实现gzip2压缩打包（注意：后缀名一定要符合通用规范)
COMMENT
#输出
echo "文件new.txt中的不同部分：" > result.txt
diff new.txt orig.txt | grep "$(cat new.txt)" >> result.txt
echo -e "\n\n\n文件orig.txt中的不同部分：" >> result.txt
diff new.txt orig.txt | grep "$(cat orig.txt)" >> result.txt


#压缩打包
tar -cjvf result.tar.bz2 result.txt

exit 0
