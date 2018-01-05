#! /bin/bash
echo -n "bash版本：" >> info.txt
echo $BASH_VERSION >> info.txt
echo -n "X display名字：" >> info.txt
echo $DISPLAY >> info.txt
echo -n "用户主目录信息：" >> info.txt
echo $HOME >> info.txt
