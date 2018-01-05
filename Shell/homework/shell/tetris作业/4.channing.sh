#!/bin/bash


################################################################################
####参数定义
################################################################################

#颜色定义
colorCnt=7  #颜色总数
red=1		    #红色
green=2	    #绿色
yellow=3	  #黄色
blue=4	    #蓝色
fuchisa=5	  #紫红色
cyan=6	    #青色（蓝绿色）
white=7	    #白色

#方块定义，7大类19种样式
#前8位为方块坐标，后2位为方块刚出现的时候的位置

box0_0=(0 0 0 1 1 0 1 1 0 4)

box1_0=(0 1 1 1 2 1 3 1 0 3)
box1_1=(1 0 1 1 1 2 1 3 -1 3)

box2_0=(0 0 1 0 1 1 2 1 0 4)
box2_1=(0 1 0 2 1 0 1 1 0 3)

box3_0=(0 1 1 0 1 1 2 0 0 4)
box3_1=(0 0 0 1 1 1 1 2 0 4)

box4_0=(0 2 1 0 1 1 1 2 0 3)
box4_1=(0 1 1 1 2 1 2 2 0 3)
box4_2=(1 0 1 1 1 2 2 0 -1 3)
box4_3=(0 0 0 1 1 1 2 1 0 4)

box5_0=(0 0 1 0 1 1 1 2 0 3)
box5_1=(0 1 0 2 1 1 2 1 0 3)
box5_2=(1 0 1 1 1 2 2 2 -1 3)
box5_3=(0 1 1 1 2 0 2 1 0 4)

box6_0=(0 1 1 0 1 1 1 2 0 3)
box6_1=(0 1 1 1 1 2 2 1 0 3)
box6_2=(1 0 1 1 1 2 2 1 -1 3)
box6_3=(0 1 1 0 1 1 2 1 0 4)

boxTypeCnt=7              #方块类型总数
boxLength=8               #方块坐标长度
countBox=(1 2 2 2 4 4 4)  ##各种方块旋转后可能的样式数目  

#运行时数据
nextBoxColor=0          #下一个方块
nextBoxType=0           #下一个方块的种类
nextBoxStyle=0          #下一个方块的样式
curBoxLoction=()        #当前方块的位置定义
curBoxColor=0           #当前方块的颜色
curBoxType=0            #当前方块的种类
curBoxStyle=0           #当前方块的样式
curBoxX=8               #当前方块的x坐标
curBoxY=25              #当前方块的y坐标



################################################################################
#用途:随机创建各种类型/颜色的方块
#参数：无
#调用方法：CreateBox
#返回值 :TRUE or FALSE
#说明：无
################################################################################
createBox( )
{

	local  x y   #定义本地变量，x/y分别为显示的坐标系

	##清除显示方块
	if (( ${#nextBox[@]} != 0 ))
	then
	  for ((i=0; i < $boxLength; i += 2))
	  do
	    ((y = curBoxX+ ${nextBox[$i]}))        #获取x坐标   
	    ((x = curBoxY+2 * ${nextBox[$i + 1]})) #获取y坐标
	    echo -ne "\033[${y};${x}H\040\040"     #根据xy显示背景色
	  done
	fi

	#随机生成与预显示方块
	(( nextBoxType  = RANDOM % $boxTypeCnt ))              #方块类型
	(( box_NexStyle = RANDOM % ${countBox[$nextBoxType]})) #各种方块旋转类型
	(( nextBoxColor = RANDOM % $colorCnt + 1))             #颜色
	  
	nextBox=(`eval 'echo ${box'$nextBoxType'_'$nextBoxStyle'[@]}'`)
	echo -ne "\033[1m\033[3${nextBoxColor}m\033[4${nextBoxColor}m"

	for ((i = 0; i < $boxLength; i += 2))
	do
	  ((y = curBoxX+ ${nextBox[$i]}))         #获取x坐标
	  ((x = curBoxY+2 * ${nextBox[$i + 1]}))  #获取y坐标
	  echo -e "\033[${y};${x}H[]"             #根据xy显示括号色
	done

	echo -e "\033[0m\033[?25l" #清除光标

}

################################################################################
#用途:后台运行函数，循环一秒创建方块
#参数：无
#调用方法：backup
#返回值 :TRUE or FALSE
#说明：无
################################################################################
backup( )
{
	while :
	do 
		createBox #创建方块
		sleep 1   #休眠一秒，即每分钟创建一次
	done 
}

################################################################################
#用途:主程序入口，屏幕显示信息提示及程序退出
#参数：无
#调用方法：main
#返回值 :TRUE or FALSE
#说明：无
################################################################################
main( )
{
	clear		
	local curPid   #定义本地变量，获取后台运行的ID
	local stopKey  #记录从终端读取用户输入值

	backup &       #创建方块后台运行
	curPid=$!      #获取后台运行的ID

	echo "程序正在运行，退出请按输入y"
	read stoppedKey   #从终端读取用户输入值

  #如果输入值为"y"，则进入while循环
	while [  $stoppedKey = "y" ]
	do  
	  kill $curPid >/dev/null 2>&1 #杀死当前进程
	  clear 
	  echo "已退出程序" 
	  break 
	done
}

main
