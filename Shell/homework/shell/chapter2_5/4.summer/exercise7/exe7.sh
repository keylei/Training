#! /bin/bash 
#==========================================================================================================
#  7、观察exercise7目录下的视频，在该目录下写一个脚本要100%符合视频中脚本运行的要求，该脚本退出方式有两种
# 	a.)ctrl + C 强制退出
#   b.)超过60s自行退出
#========================================================================================================== 
echo
TMOUT=60
let TIME_LIMIT=60   
echo "Hit Control-C to exit before 60 seconds."
# 判断时间是否到达60s然后退出
while [ $SECONDS -lt $TIME_LIMIT ] 
do 
   printf "Please input your name:"
   read input
   let TMOUT=$TIME_LIMIT-"$SECONDS"
   if [ "$input" ==  "" ]
   then 
       echo
   else
       echo "$input has run the script $SECONDS seconds."
   fi
echo
done 
exit 0
