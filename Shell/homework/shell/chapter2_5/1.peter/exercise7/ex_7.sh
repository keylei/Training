#! /bin/bash

#==============================================================================
#7、观察exercise7目录下的视频，在该目录下写一个脚本要100%符合视频中脚本运行的要求，
#   该脚本退出方式有两种
#	a.)ctrl + C 强制退出
#  	b.)超过60s自行退出
#==============================================================================

TIME_LIMIT=60		#设置时间限制为60秒

echo  "Control-C to exit before $TIME_LIMIT seconds."	#显示提示信息

#while循环判断时间是否小于60s
while [ "$SECONDS" -le "$TIME_LIMIT" ];do 	
	TMOUT=$[$[TIME_LIMIT]-$[SECONDS]]		#设置timeout时间		
	echo -n "Please input your name:";read name	#提示信息
		
	#时间为60s自动退出,否则输出脚本运行信息
	if [ "$SECONDS" -eq "$TIME_LIMIT" ];then 
		echo "Time out!" 
		exit 0
	else
		echo -e "${name^} has run this script $SECONDS second(s).\n"
	fi
done

exit 0

