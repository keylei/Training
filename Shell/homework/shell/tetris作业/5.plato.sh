#!/bin/bash
################################################################################
# Tetris Game
#		1、俄罗斯方块颜色随机显示
# 	2、俄罗斯方块形状随机显示	
#		3、每隔1秒更新一次形状与颜色
################################################################################

echo -ne "\033[?25l"		#隐藏光标

leftMargin=5						#方块与左侧边缘距离
topMargin=3							#方块与顶部边缘距离

#定义方块的颜色(七种)
red=1					#红色
green=2				#绿色
yellow=3			#黄色
blue=4				#蓝色
purple=5			#紫色
cyan=6				#青色
white=7				#白色
#将七种颜色放到数组变量colorArray中
colorArray=($red $green $yellow $blue $purple $cyan $white)		

#用坐标定义方块的七种形状数组变量(毎两位元素表示一个坐标，偶数位为Y轴，奇数位为X轴)
#毎种旋转状态用8个元素表示，形状O有1种旋转状态，I、Z、S有2种，J、L、T有4种,共19种
boxO=(0 0 0 1 1 0 1 1)
boxI=(0 2 1 2 2 2 3 2 1 0 1 1 1 2 1 3)
boxZ=(0 0 0 1 1 1 1 2 0 1 1 0 1 1 2 0)
boxS=(0 1 0 2 1 0 1 1 0 0 1 0 1 1 2 1)
boxJ=(0 1 0 2 1 1 2 1 1 0 1 1 1 2 2 2 0 1 1 1 2 0 2 1 0 0 1 0 1 1 1 2)
boxL=(0 1 1 1 2 1 2 2 1 0 1 1 1 2 2 0 0 0 0 1 1 1 2 1 0 2 1 0 1 1 1 2)
boxT=(0 1 1 1 1 2 2 1 1 0 1 1 1 2 2 1 0 1 1 0 1 1 2 1 0 1 1 0 1 1 1 2)

#将七种形状的数组内容的定义放到新的数组变量box中
box=(${boxO[*]} ${boxI[*]} ${boxZ[*]} ${boxS[*]} ${boxJ[*]} ${boxL[*]} ${boxT[*]})

#方块七种形状旋转后的形态数分别放在boxArr数组中
boxArr=(1 2 2 2 4 4 4)		
			
#boxOffsetArr存放方块七种形状在box数组中的偏移，毎8个元素为一个偏移量，boxO第1个元素
#开始偏移为0，boxI首部为第9个元素，偏移量为1，boxZ首部为第25个元素，偏移量为3，...
boxOffsetArr=(0 1 3 5 7 11 15)		

boxPosition=()        				#初始化方块位置数组元素变量
boxColor=0       							#初始化方块颜色值
boxShapeType=0        				#初始化方块形状类型
boxRotationType=0        			#初始化方块旋转状态类型

#定义函数showBox，随机显示方块19种旋转形态和7种随机颜色
showBox()
{
	local posY 		#局部变量posY表示19种旋转状态数组中的偶数位元素坐标
	local posX 		#局部变量posX表示19种旋转状态数组中的奇数位元素坐标
	local index		#局部变量index表示19种旋转状态的毎8个元素的索引
	((boxShapeType = RANDOM % ${#boxOffsetArr[*]}))				  #随机选择方块形状类型
	((boxRotationType = RANDOM % ${boxArr[$boxShapeType]})) #随机选择方块旋转状态类型
		
	#由于19种旋转状态都由8个元素表示，找到每种旋转状态的索引需要乘以8
	index=(${boxOffsetArr[$boxShapeType]} + $boxRotationType)*8

	#通过for循环8次遍历索引之后8个元素
	for ((i = 0; i < 8; i ++, index++))
	do		
  	boxPosition[$i]=${box[$index]}		 #获取表示方块位置的8个元素		
	done

	((boxColor = ${colorArray[ RANDOM % ${#colorArray[*]} ]}))		#随机选择方块颜色
	echo -ne "\033[1m\033[7m\033[3${boxColor}m\033[4${boxColor}m" #显示方块颜色

	#通过for循环4次输出表示方块位置的4组坐标元素
	#posY为偶数位元素表示Y轴坐标，posX为奇数位元素表示X轴坐标
	for ((i = 0; i < 8; i += 2))
	do
		#依次获取boxPosition数组元素，如${boxPosition[0]、${boxPosition[2]}
		((posY = topMargin + ${boxPosition[$i]}))		
			
		#依次获取boxPosition数组元素，如${boxPosition[1]、${boxPosition[3]}
		#由于X轴方向单个字符宽度较小，需要两倍的宽度来表示一个方块
		((posX = leftMargin + 2 * ${boxPosition[$i + 1]}))	
	
		echo -ne "\033[${posY};${posX}H[]\n"						 #显示方块旋转状态
	done
	echo -ne "\033[0m"			#关闭所有属性
}

while true
do
	clear										#清屏
	showBox									#调用函数showBox
	sleep 1									#设置延时1秒
done


