#! /bin/bash
#根据视频要求完成编程

#设置系统时间
TIME_LIMIT=59
INTERVAL=1
TMOUT=60
#显示要求
echo -e "\nHit Control-C to exit before 60 seconds" 
#在条件内的
while [ "$SECONDS" -le "$TIME_LIMIT" ]
do  
#在屏幕上输入个人名称
   echo -n -e "\nplease input you name:"; read name
   if [ "$SECONDS" -eq 1 ]
   then
      units=second
   else
      units=seconds
    fi
#显示用户运行时间
   echo "$name has run the script $SECONDS $units."
done

exit 0













