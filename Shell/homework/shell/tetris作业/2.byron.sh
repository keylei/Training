#!/bin/bash

########################Constant and variable definition#######################

###############################Constant define
# 方块形状，总共有7种方块（O,I,Z,S,J,L,T），每种方块在不同角度下有不同表现
# 每个方块的形状用4组坐标（8个数据）表示，坐标形式为（y，x）
O_BOX=(0 0 0 1 1 0 1 1)
I_BOX=(0 2 1 2 2 2 3 2 1 0 1 1 1 2 1 3)
Z_BOX=(0 0 0 1 1 1 1 2 0 1 1 0 1 1 2 0)
S_BOX=(0 1 0 2 1 0 1 1 0 0 1 0 1 1 2 1)
J_BOX=(0 1 0 2 1 1 2 1 1 0 1 1 1 2 2 2 0 1 1 1 2 0 2 1 0 0 1 0 1 1 1 2)
L_BOX=(0 1 1 1 2 1 2 2 1 0 1 1 1 2 2 0 0 0 0 1 1 1 2 1 0 2 1 0 1 1 1 2)
T_BOX=(0 1 1 1 1 2 2 1 1 0 1 1 1 2 2 1 0 1 1 0 1 1 2 1 0 1 1 0 1 1 1 2)

# 所有方块的总数据源
BOX_SHAPES=(${O_BOX[@]} ${I_BOX[@]} ${Z_BOX[@]} ${S_BOX[@]} ${J_BOX[@]} ${L_BOX[@]} ${L_BOX[@]})

# 每种方块儿的状态数组，顺序与BOX_SHAPES中的顺序一致
BOX_SHAPE_TYPE_COUNT=(1 2 2 2 4 4 4)

# 每种方块数据，在BOX_SHAPES中的起始地址索引
BOX_SHAPE_DATA_INDEX=(0 1 3 5 7 11 15)

# 方块数据长度
BOX_SHAPE_DATALEN=8

# 颜色定义
BLACK='\033[40;30m' 
RED='\033[41;31m' 
GREEN='\033[42;32m' 
YELLOW='\033[43;33m' 
BLUE='\033[44;34m' 
PURPLE='\033[45;35m' 
CYAN='\033[46;36m' 
LIGHTGRAY='\033[47;37m'

# 颜色名称数组，生成随机颜色时使用
declare -a COLOR_NAMES=('BLACK' 'RED' 'GREEN' 'YELLOW' 'BLUE' 'PURPLE' 'CYAN' 'LIGHTGRAY')

###############################variant definition
curBoxShapeIdx=0   #当前方块儿的形状索引(0~7)
curBoxShapeType=0  #当前方块儿的形状索引，数据上限来源于BOX_SHAPE_TYPE_COUNT
curBoxShapeDate=0  #当前方块儿形状数据，方便后续擦除和位移显示
curBoxPos=(0 0)    #当前方块儿的位置（整个方块儿在屏幕上的位置）
curBoxClrIdx=1     #当前方块儿的颜色索引(0~7)


##############################functions definition#############################

############方块数据更新函数###########
# $1 方块儿的形状索引（0~7）
# $2 方块儿的形状类型 (0~4)，形状不同数值各异
####################################
updateCurBoxData()
{
  #防呆 输入数字检查、参数范围检查
	[ $# != 2 ] && { echo "randomBoxElement:参数数量错误！";return 1; }
	[ ! -z $(echo $1 | sed 's/[0-9]//g') ] && { echo "randomBoxElement:参数1请输入数字参数！0/1";return 1; }
	[ ! -z $(echo $2 | sed 's/[0-9]//g') ] && { echo "randomBoxElement:参数2请输入数字参数！0/1";return 1; }
	[ $1 -ge ${#BOX_SHAPE_TYPE_COUNT[@]} ] || [ $1 -lt 0 ] && { echo "randomBoxElement:ShapeIndx 值错误！";return 1; }
	[ $2 -gt ${BOX_SHAPE_TYPE_COUNT[$1]} ] || [ $2 -lt 0 ] && { echo "randomBoxElement:ShapeTypeIndx 值错误！";return 1; }

	local boxShapeIndx=$1
	local boxShapeType=$2
	local srcIndx=0
  local dstIndx=0
	
	# 计算在数据源BOX_SHAPES中的数据偏移
  (( srcIndx = (${BOX_SHAPE_DATA_INDEX[$boxShapeIndx]} + boxShapeType) * 8 ))

	# 将数据更新到当前显示数据数组中
  for ((dstIndx = 0; dstIndx < 8; dstIndx++, srcIndx++))
  do
		curBoxShapeDate[$dstIndx]=${BOX_SHAPES[$srcIndx]};
  done
}

############方块显示函数###########
# $1 控制渲染方式
#    0：擦除渲染
#    1：正常渲染
#################################
renderBox()
{	
	#防呆输入整形数字、输入参数范围检查
	[ $# != 1 ] && { echo "renderBox function:参数数量错误！";return 1; }
	[ ! -z $(echo $1 | sed 's/[0-9]//g') ] && { echo "renderBox:请输入整形数字参数！0/1";return 1; }
	[ $1 -gt 1 ] || [ $1 -lt 0 ] && { echo "renderBox:参数值错误！请输入0/1";return 1; }

	local isDraw=$1
	local boxPixe="[]"                    #每一个方格的显示内容
	local fommateStr="\033[7m\033[?25l"   #显示样式字符串，\033[1m：高亮显示
  local dataIndx=0                      #BOX_SHAPES数组中的方块数据读取索引                 
	local yCursorPos=0                    #光标位置
	local xCursorPos=0

	# 控制显示渲染或者擦除渲染
	if (( isDraw == 0 ))
	then
		boxPixe="\040\040" 
	else
		fommateStr=$fommateStr"${!COLOR_NAMES[$curBoxClrIdx]}"   #加入颜色控制字符
	fi

	# 更新渲染数据，即坐标数据
	for ((dataIndx=0; dataIndx<BOX_SHAPE_DATALEN; dataIndx+=2 ))
	do
		(( yCursorPos=${curBoxPos[0]}+${curBoxShapeDate[$dataIndx]} ))
		#2*shapedata中的X坐标，是因为“[]”显示占用两个字符位置
		(( xCursorPos=${curBoxPos[1]}+2*${curBoxShapeDate[$dataIndx+1]} ))
		fommateStr=$fommateStr"\033[${yCursorPos};${xCursorPos}H${boxPixe}"
	done
	
	# 输出渲染数据
	fommateStr=$fommateStr"\033[0m"
	echo -n $fommateStr
}

############Box随机数据更新函数###########
# $1 顺序产生唯一控制参数
#    0：接受出现与上次一样的随机数
#    1：不接受出现与上次一样的随机数
#################################
randomBoxElement()
{
  #防呆TBC 输入数字检查（字符，浮点）   输入参数范围检查
	[ $# != 1 ] && { echo "renderBox function: incorrect input parameter";return 1; }
	local isUnique=$1
  local newCurBoxShapeIdx=0
  local newCurBoxShapeType=0
  local newCurBoxClrIdx=0
	(( newCurBoxShapeIdx=RANDOM%${#BOX_SHAPE_TYPE_COUNT[@]} ))
	(( newCurBoxShapeType=RANDOM%${BOX_SHAPE_TYPE_COUNT[$curBoxShapeIdx]} ))
	(( newCurBoxClrIdx=RANDOM%${#COLOR_NAMES[@]} ))
  
  # 唯一标示符控制生成方式
	if (( isUnique != 0 ))
	then
		while (( curBoxShapeIdx == newCurBoxShapeIdx ))
		do
			(( newCurBoxShapeIdx=RANDOM%${#BOX_SHAPE_TYPE_COUNT[@]} ))
		done
		while (( curBoxClrIdx == newCurBoxClrIdx ))
		do
			(( newCurBoxClrIdx=RANDOM%${#COLOR_NAMES[@]} ))
		done
	fi
  curBoxShapeIdx=$newCurBoxShapeIdx
	curBoxShapeType=$newCurBoxShapeType
	curBoxClrIdx=$newCurBoxClrIdx
}


##############################Main program entrancery##########################
main()
{
	clear	               #清除当前屏幕显示

	curBoxPos=(10 10)    #设置方块显示位置

	local renderDataStr=""
	 while true                       #循环显示方块
	 do
		
		randomBoxElement 1              #生成随机方块数据 1：不生成重复随机数
		updateCurBoxData $curBoxShapeIdx $curBoxShapeType

		renderDataStr=`renderBox 1`     #更新形状数据 1：正常刷新
		clear
	  echo -ne $renderDataStr         #输出显示
	  
		sleep 1
		
		(( curBoxClrIdx=RANDOM%${#COLOR_NAMES[@]} )) #变换颜色
    
		renderDataStr=`renderBox 1`
		echo -ne $renderDataStr
		
		sleep 1
	 done
}

main

exit 0

