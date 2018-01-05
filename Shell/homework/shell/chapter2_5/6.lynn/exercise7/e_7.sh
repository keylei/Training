#! /bin/bash
<<COMMENT
观察exercise7目录下的视频，在该目录下写一个脚本要100%符合视频中脚本运行的要求，该脚本退出方式有两种
	a.)ctrl + C 强制退出
  b.)超过60s自行退出
COMMENT
#提示信息：
	echo -e "\nHit Control-C to exit before 60 seconds\n"

#设置变量：
	let TIMELIMIT=60
	TMOUT=60

#循环：
	while [ $TMOUT -gt 0 ]
	do
		echo -n "please input your name:"
		read name
	  let TMOUT=$TIMELIMIT-$SECONDS	
	  if [ $SECONDS -lt $TIMELIMIT ]
		then
			if [ $SECONDS == "0" ] || [ $SECONDS == "1" ]
			then
				echo -e "$name has run the script $SECONDS second.\n"
			else	
				echo -e "$name has run the script $SECONDS seconds.\n"
			fi
		else
			echo 
		fi
	done	

exit 0
