#!/bin/bash

BASEDIR=`dirname $0`/.. 
BASEDIR=`(cd "$BASEDIR"; pwd)` #获取当前路径
PROGRAM=$BASEDIR/ex_4.sh       #获取脚本名          
echo $PROGRAM 
CRONTAB_CMD="* * * * * channing $PROGRAM" #保存当前路径变量与执行配置

(crontab -l 2>/dev/null | grep -Fv $PROGRAM; echo "$CRONTAB_CMD") | crontab - 
COUNT=`crontab -l | grep $PROGRAM | grep -v "grep"|wc -l ` 

if [ $COUNT -lt 1 ]; then #如过成功添加过则不再添加
        echo "fail to add crontab $PROGRAM" 
        exit 1 
fi 
crontab -l #查看是否添加
