#! /bin/bash
#============================================================================================================================================================================================
# 7、观察exercise7目录下的视频，在该目录下写一个脚本要100%符合视频中脚本运行的要求，该脚本退出方式有两种
# 	a.)ctrl + C 强制退出
#  	b.)超过60s自行退出
#============================================================================================================================================================================================

TIME_LIMIT=60
TMOUT=60									#设定超时秒数

echo
echo "Hit Control-C to exit before $TIME_LIMIT seconds."
echo

while [ "$SECONDS" -lt "$TIME_LIMIT" ]		#当脚本运行秒数小于TIME_LIMIT时
do 	

	echo -n "please input your name: "		
	read name
    let TMOUT=TIME_LIMIT-$SECONDS			#计算超时秒数
 
    if [ "$name" != "" ]					#若输入不为空，执行echo
	then
		echo "$name has run the script $SECONDS seconds."
	fi

	echo		
done

exit 0
