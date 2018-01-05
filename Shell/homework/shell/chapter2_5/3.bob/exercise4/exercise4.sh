#! /bin/bash
#在exercis4目录下写一个脚本，实现对"orig.txt"和"new.txt"中不同部分输出到该目录"result.txt"中，然后用tar来实现gzip2压缩打包（注意：后缀名一定要符合通用规范）

#输出orig.txt与new.txt内容有差异的行
echo -e "\"orig.txt\"与\"new.txt\"内容有差异的行:" > result.txt | diff -y orig.txt new.txt | grep -e "|" >> result.txt
#输出new.txt与orig.txt内容多出的行
echo -e "\n\"new.txt\"比\"orig.txt\"内容多出的行:" >> result.txt | diff -y orig.txt new.txt | grep -e ">" >> result.txt
#输出orig.txt与new.txt内容多出的行
echo -e "\n\"orig.txt\"比\"new.txt\"内容多出的行:" >> result.txt | diff -y orig.txt new.txt | grep -e "<" >> result.txt

#将orig.txt和new.txt内容不同部分输出至result.txt文件中
#echo -e "\n\n\"orig.txt\"比\"new.txt\"内容不同部分:" >> result.txt | cat new.txt orig.txt | sort | uniq -u >> result.txt
#将result文件压缩
tar -czvf ex4_result.tar.gz ./result.txt

exit 0
