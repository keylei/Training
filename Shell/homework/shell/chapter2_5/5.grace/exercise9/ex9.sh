#! /bin/bash
#=============================================================================================================================
# 9、参考exercise9目录下的视频，在该目录下写一个脚本，该脚本执行后需实现如下目的：
#	 a.) 倒计时10秒钟
#  b.) 10秒内输入"y"并回车，则将该目录下a.txt改名为b.txt
#  c.) 10秒内输入其它字符并回车，则放弃更改a.txt名称
#  d.) 如果10秒内没有任何输入并回车，则视为放弃修改a.txt名称
#  这题需要达到的效果请参考该目录下视频，请100%符合视频实现的效果
#============================================================================================================================
  

#echo -n Count:
touch a.txt                                   
#10s倒计时函数
progress ()
{  
tput sc  
  
count=10                                      #设倒计时10s
while true;  
do  
        if [ $count -gt 0 ];
          then  
          let count--;  
          sleep 1;  
          tput rc  
          tput ed  
          echo -n "Do you want to mv a.txt b.txt?(y/n)count down $count" 
        else  
          echo "give up to mv a.txt to b.txt"
          exit 0;  
        fi  
done  
}

progress &                                     #将progress放到后台运行
#mv 函数：将该目录下a.txt改名为b.txt
move ()
{
  read s                                       #读用户输入的数据（y或者其他参数）

  MYSELF=$!
  kill $MYSELF > /dev/null 2>&1                #杀死进程

  if [ $s == "y" ];
        then
          mv a.txt b.txt;
          echo "a.txt has been changed name to b.txt"
          exit 0;
        else
          echo "give up to mv a.txt to b.txt!"
  fi
  mv a.txt b.txt
}

move 
exit 0
