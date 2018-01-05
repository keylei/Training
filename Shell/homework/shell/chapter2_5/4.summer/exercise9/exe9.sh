#! /bin/bash
#==========================================================================================================
#  9、参考exercise9目录下的视频，在该目录下写一个脚本，该脚本执行后需实现如下目的：
#   	a.) 倒计时10秒钟
#     b.) 10秒内输入"y"并回车，则将该目录下a.txt改名为b.txt
#     c.) 10秒内输入其它字符并回车，则放弃更改a.txt名称
#     d.) 如果10秒内没有任何输入并回车，则视为放弃修改a.txt名称
#     这题需要达到的效果请参考该目录下视频，请100%符合视频实现的效果
#==========================================================================================================
printf "Do you want to mv a.txt b.txt (y/n) count down: "
tput sc 
TMOUT=10
count=10
name()
{
while true;  
do   
if [ $count -ge 0 ]
then  
     let count-- 
     sleep 1;  
     tput rc  
     tput ed  
     echo -n $count   
else  
     echo
     echo "Give up to mv a.txt to b.txt."
     exit 0
fi  
done
}
name &               #将函数放在后台运行
MYSELF=$!            #使用PID结束进程放在后台的进程
read input
if [ "$input" == "y" ]
then
      mv a.txt b.txt
		  echo "a.txt has been changed name to b.txt."
		  kill $MYSELF  
else
		  echo "Give up to mv a.txt to b.txt."
      kill $MYSELF
fi
exit 0
  

