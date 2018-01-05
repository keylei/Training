#! /bin/bash

#==============================================================================
#9、参考exercise9目录下的视频，在该目录下写一个脚本，该脚本执行后需实现如下目的：
#	a.) 倒计时10秒钟
#	b.) 10秒内输入"y"并回车，则将该目录下a.txt改名为b.txt
#	c.) 10秒内输入其它字符并回车，则放弃更改a.txt名称
#	d.) 如果10秒内没有任何输入并回车，则视为放弃修改a.txt名称
#   这题需要达到的效果请参考该目录下视频，请100%符合视频实现的效果
#==============================================================================

#倒计时函数
countdown ()
{
	echo -en "Do you want to \"mv a.txt b.txt\"? (y/n) count down:" 
	tput sc  	#保存光标位置
 	echo -n $count
	while [ $count -gt 0 ];do 
                tput rc	#恢复光标位置
                tput ed	#删除光标后内容
                let count--  
                echo -n $count
                sleep 1
	done 
}

count=10	#设置倒计时时间
TMOUT=$count	#设置TimeOut时间

countdown &	#后台运行countdown函数
countdownpid=$!	#记录countdown后台pid进程号

read choose
if [ "$choose" == "y" ];then
	mv a.txt b.txt
	echo  "a.txt has been changed name to b.txt." 
else
	echo "give up to mv a.txt b.txt"
fi

kill $countdownpid	#杀死后台循环函数

exit 0

