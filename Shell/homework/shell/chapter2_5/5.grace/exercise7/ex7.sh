#! /bin/bash
#=============================================================================================================================
# 7、观察exercise7目录下的视频，在该目录下写一个脚本要100%符合视频中脚本运行的要求，该脚本退出方式有两种
#	a.)ctrl + C 强制退出
# b.)超过60s自行退出
#=============================================================================================================================
#progressdots.sh
#定义函数progress显示进度条

TIME_LIMIT=60 #限制时间最大为60s
echo "Hit CTRL-C to exit before $TIME_LIMIT seconds." #按CTRL+C自行退出

while [ "$SECONDS" -lt "$TIME_LIMIT" ]
do
  echo "Please input your name:"
  read -t 5 name                                      #不操作则每5s显示时间
  Time=${60-$SECONDS}                                 #剩余时间
  if [ $Time -eq 0 ]
    then 
      exit 0
    else
      echo "$name has run the script $SECONDS seconds"
  fi
done

exit 0

    





