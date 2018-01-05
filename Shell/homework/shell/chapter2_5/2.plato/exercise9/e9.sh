#! /bin/bash
#============================================================================================================================================================================================
# 9、参考exercise9目录下的视频，在该目录下写一个脚本，该脚本执行后需实现如下目的：
# 	a.) 倒计时10秒钟
#	b.) 10秒内输入"y"并回车，则将该目录下a.txt改名为b.txt
#  	c.) 10秒内输入其它字符并回车，则放弃更改a.txt名称
#  	d.) 如果10秒内没有任何输入并回车，则视为放弃修改a.txt名称
#  	这题需要达到的效果请参考该目录下视频，请100%符合视频实现的效果
#============================================================================================================================================================================================

# d.)10秒内没有输入，放弃更改
TMOUT=10					#设置超时秒数

# a.)倒计时10秒
echo -n "Do you want to mv a.txt b.txt? (y/n) count down:"
 
Count_Down()				#定义函数Count_Down
{
	tput sc  				#保存当前光标位置
	  
	count=10  
	while true;  
	do  
		if [ $count -gt 0 ]
		then  
			let count--  
			sleep 1 
			tput rc  		#显示输出			 		
			echo -n $count
		
		else  
			exit 0  
		fi  
	done
}
Count_Down &				#后台运行

MYSELF=$!					#保存函数Count_Down进程号

# b.)10秒内输入"y"，更改
read input
if [ "$input" == "y" ] 
then
	
	mv a.txt b.txt			#a.txt改名为b.txt
	echo "a.txt has been changed name to b.txt."
	kill $MYSELF	#杀死后台进程
	
# c.)输入其它字符，放弃更改
else
	echo "give up to mv a.txt to b.txt!"
	kill $MYSELF	#杀死后台进程
fi

exit 0
