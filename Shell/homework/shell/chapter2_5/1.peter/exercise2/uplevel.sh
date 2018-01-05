#! /bin/bash

#==============================================================================
#2、在exercise2目录下创建一个脚本名为"uplevel.sh"和一个叫"text"的文本文件，其中
#   "text"的用户权限是root:root(o没有修改的权限)，而"uplevel.sh"具有suid和sgid标志
#   位，该脚本内要输出“hello world”到text文本，请实现
#==============================================================================

#临时变更为root:root,拥有在txt中写入"hello world"权限.
sudo echo "Hello World!" >> text

exit 0
