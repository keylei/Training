#! /bin/bash
#题目要求
#参考exercise9目录下的视频，在该目录下写一个脚本，该脚本执行后需实现如下目的：
#a.) 倒计时10秒钟
#b.) 10秒内输入"y"并回车，则将该目录下a.txt改名为b.txt
#c.) 10秒内输入其它字符并回车，则放弃更改a.txt名称
#d.) 如果10秒内没有任何输入并回车，则视为放弃修改a.txt名称
#这题需要达到的效果请参考该目录下视频，请100%符合视频实现的效果
#定义系统变量并赋值
TIME_LIMIT=10
INTERVAL=1
TMOUT=10
#计时器函数
cal()
{
#输入显示提示
echo -n "Do you want to mv a.txt b.txt? (y/n) count down :"
#保存当前光标位置
tput sc  　　

count=10
#判断时间是否超时
while true;  
do 
        if [ $count -gt 0 ];then
                let count--;
                sleep 1;
                tput rc
                echo -n $count;
		else
			exit  1
        fi  
done 
}
#判断是否更改文件函数
inp()
{
read input
#判断是否更改文件
if  [ "$input" == y ]
 then
     mv a.txt b.txt
     echo -e "a.txt has been changed name to b.txt "
  else
     echo -e "give up to mv a.txt b.txt!"
 fi
}
#将函数cal放置后台运行
cal &
#获取cal函数运行的进程ID
myself=$!
#转移控制函数inp
inp
#关闭cal函数进程
kill $myself

exit 0
  













