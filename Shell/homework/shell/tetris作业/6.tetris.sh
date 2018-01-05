#===============================================================================
#1、俄罗斯方块颜色随机显示
#2、俄罗斯方块形状随机显示
#3、每隔1秒更新一次形状与颜色
#===============================================================================
#! /bin/bash 

#===============================参数&&变量定义====================================
#通过旋转，每种方块的显示的样式可能有几种
box0=(0 0 0 1 1 0 1 1)
box1=(0 2 1 2 2 2 3 2 1 0 1 1 1 2 1 3)
box2=(0 0 0 1 1 1 1 2 0 1 1 0 1 1 2 0)
box3=(0 1 0 2 1 0 1 1 0 0 1 0 1 1 2 1)
box4=(0 1 0 2 1 1 2 1 1 0 1 1 1 2 2 2 0 1 1 1 2 0 2 1 0 0 1 0 1 1 1 2)
box5=(0 1 1 1 2 1 2 2 1 0 1 1 1 2 2 0 0 0 0 1 1 1 2 1 0 2 1 0 1 1 1 2)
box6=(0 1 1 1 1 2 2 1 1 0 1 1 1 2 2 1 0 1 1 0 1 1 2 1 0 1 1 0 1 1 1 2)
#所有其中方块的定义都放到box变量中
box=(${box0[@]} ${box1[@]} ${box2[@]} ${box3[@]} ${box4[@]} ${box5[@]} ${box6[@]})
#各种方块在box数组中的偏移
boxOffset=(0 1 3 5 7 11 15)
#各种方块旋转后可能的样式数目，主要用于形状确定后，随机确定角度
rotateCount=(1 2 2 2 4 4 4)
#颜色数组，主要用于随机产生颜色
colourArry=(41 42 43 44 45 46 47)
#边缘距离
top=3
left=3
#当前x,y坐标
currentX=10
currentY=5
#当前方块数据信息
declare -a curBoxData
#==================================函数=========================================
#随机产生各种数据
function randomBox()
{
  #recIndex：源数据索引；desIndex：目的索引；主要用于将源数据传递给目的数组
  local recIndex desIndex                    
	#随机产生方块号
	(( boxIndex = $RANDOM % ${#rotateCount[@]} ))    
	#随机产生方块的类型
	((rotateType = $RANDOM % ${rotateCount[boxIndex]}))
	#随机产生颜色
	((colourNum = $RANDOM % ${#colourArry[@]}))
	#找到所在box中的起始位置
	((recIndex = (${boxOffset[boxIndex]} + rotateType) * ${#box0[@]}))
	for(( desIndex = 0 ;desIndex < ${#box0[@]};desIndex ++))
	do
		((curBoxData[desIndex] = ${box[recIndex+desIndex]}))
	done
}

#绘制当前方块，传第一个参数，0表示擦除方块，1表示绘制方块  
function drawBox()
{
	local i x y                               #定义i为循环变量x,y分别为x，y坐标

	if (($1 == 0))                            #$1：第一个参数
	then                                      #8个数四个点循环4次
		clear                                   #第一个参数为0时清屏

		echo -e "\033[${colourArry[$colourNum]}m\033[1m"     
		for ((i = 0;i < ${#box0[@]};i += 2))        
		do                                           
			((x = left + 2 * (currentX + ${curBoxData[i]})))    
			((y = top + currentY + ${curBoxData[i+1]}))          
                                           #x,y：边缘距离+当前的（x,y）坐标 
			echo -e "\033[${y};${x}H  "          #显示图标
		done
	fi

	echo -e "\033[0m"                        #关闭所有属性
}

#===============================主程序部分=======================================
echo -e "\033[2J"													 #清屏
while :																		 #while循环调用函数使程序一直运行 
do
  randomBox                                #调用randomBox函数随机生成数据
  echo -ne "\033[?25l"                     #隐藏光标
  drawBox 1                                #1是drawBox函数第一个参数作用：绘制方块
  sleep 1
  drawBox 0                                #0是drawBox函数第一个参数作用：擦除方块
done

exit 0

