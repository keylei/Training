#! /bin/bash

###############################################################
#1、俄罗斯方块颜色随机显示
#2、俄罗斯方块形状随机显示
#3、每隔1秒更新一次形状与颜色
###############################################################
#定义起始点X,Y的坐标
declare -i orgX=5
declare	-i orgY=5

#定义变量单个形状的长度
declare -i shapeLength
#定义变量所有形状的数量
declare -i allShapeCount
#定义形状在数组中的起始点标志位
declare -i shapeIndex

#定义方形坐标点
declare -a box0=(0 2 0 3 1 2 1 3)
#定义线形坐标点
declare -a box1=(0 3 1 3 2 3 3 3	1 0 1 1 1 2 1 3)
#定义正Z形的坐标点
declare -a box2=(0 2 1 2 1 3 2 3	1 2 1 3 2 1 2 2)
#定义反Z形的坐标点
declare -a box3=(0 3 1 2 1 3 2 2	0 1 0 2 1 2 1 3)
#定义正L形状坐标点
declare -a box4=(1 1 1 2 1 3 2 1	1 2 1 3 2 2 3 2	0 1 1 1 1 2 1 3	0 3 1 2 1 3 2 2)
#定义反L形状坐标点
declare -a box5=(0 3 1 1 1 2 1 3	0 2 0 3 1 3 2 3	1	1	1	2	1	3	2	1	0 2 1 2 2 2 2 3)
#定义凸台形状坐标点
declare -a box6=(0 3 1 2 1 3 2 2	1 1 1 2 1 3 2 2	0 2 1 2 1 3 2 2	0 2 1 1 1 2 1 3)
#将所有坐标点汇总至一个数组中
declare -a box=(${box0[*]} ${box1[*]} ${box2[*]} ${box3[*]} ${box4[*]} ${box5[*]} ${box6[*]})
#定义颜色数组[40：黑;41:深红;42:绿;43:黄;44:蓝;45:紫;46:深绿;47:白色]
declare -a colourArray=(40 41 42 43 44 45 46 47)
###############################################################

drawBox()																									#定义一个画框的方法
{
	shapeLength=${#box0[*]}																	#获取每个形状坐标点的长度
	allShapeCount=$((${#box[*]} / $shapeLength))						#获取所有形状的数量
	shapeIndex=$(($RANDOM % $allShapeCount * $shapeLength))	#随机获取形状的起始坐标

	echo -e "\033[${colourArray[$colourIndex]};35m\033[1m"	#以下输出背景色为随机色且高亮显示,将字符用紫色显示

	local x=0																								#定义输出时x的起始坐标	
	local	y=0																								#定义输出时y的起始坐标	

	for (( i = 0 ; i < shapeLength; i += 2 ))								#根据循环次数,获取相应坐标点
	do
		(( x = orgX + 2 * ${box[shapeIndex + i]}))		        #记录开始输出起始点X的坐标值,"2"为输出时至少是2个字符,如果输出字符数为n,则用"n"
		(( y = orgY + ${box[shapeIndex + i + 1]}))		        #记录开始输出起始点Y的坐标值
		echo -e "\033[${y};${x}H[]"														#每次获取坐标位置输出"[]"两个字符
	done

	echo -e "\033[0m"																				#关闭所有字体属性
}

while true
do
	clear																										#清除屏幕显示
	colourIndex=$(($RANDOM % ${#colourArray[*]}))						#随机获取颜色在数组中的编号	
	drawBox																									#执行在界面中画框的函数
	sleep 1																									#等待一秒																							
done
