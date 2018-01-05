#! /bin/bash
#在exercise2目录下创建一个脚本名为"uplevel.sh"和一个叫"text"的文本文件，其中"text"的用户权限是root:root(o没有修改的权限)，而"uplevel.sh"具有suid和sgid标志位，该脚本内要输出“hello world”到text文本，请实现
echo "hello word" >./text
