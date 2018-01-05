#! /bin/bash
<<COMMENT
参考exercise9目录下的视频，在该目录下写一个脚本，该脚本执行后需实现如下目的：
	a.) 倒计时10秒钟
  b.) 10秒内输入"y"并回车，则将该目录下a.txt改名为b.txt
  c.) 10秒内输入其它字符并回车，则放弃更改a.txt名称
  d.) 如果10秒内没有任何输入并回车，则视为放弃修改a.txt名称
  这题需要达到的效果请参考该目录下视频，请100%符合视频实现的效果
COMMENT
#恢复环境
	touch a.txt
	rm b.txt

#倒数函数
	count_num()
	{
		tput sc
		count=10
		while true;
		do
			if [ $count -gt 0 ]
			then
				let count--
				sleep 1
				tput rc
				tput ed
				echo -n $count
			else
				exit 0
			fi
		done
	}

	echo -n "Do you want to mv a.txt b.txt?(y/n)"
	count_num &
	s_pid=$!
	export TMOUT=10
	read choose

#判断输入：
	if [ "$choose" == "y" ]
		then
		mv a.txt b.txt
		#判读是否成功修改文件名：
		if [ "$?" -eq 0 ]
			then
			echo "a.txt has been changed name to b.txt."
		fi
		kill $s_pid
	else
		echo "give up to mv a.txt to b.txt!"
		kill $s_pid
	fi

exit 0
