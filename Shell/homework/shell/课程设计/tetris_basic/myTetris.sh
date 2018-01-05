#!/bin/bash

# set -e
# set -x
 
#颜色定义
cRed=1
cGreen=2
cYellow=3
cBlue=4
cFuchsia=5
cCyan=6
cWhite=7
colorTable=($cRed $cGreen $cYellow $cBlue $cFuchsia $cCyan $cWhite)
 
#位置和大小
iLeft=3  # x坐标位置
iTop=2 # y坐标位置
((iTrayLeft = iLeft + 2))
((iTrayTop = iTop + 1))
((iTrayWidth = 10))
((iTrayHeight = 15))
 
#七中不同的方块的定义
#通过旋转，每种方块的显示的样式可能有几种

# 每种样式4个小方块, 4对坐标, 所以是8个数值, 先y后x存储, 因为一个字符的宽度太断, 和高度不成比例, 所以需要乘以2
box0=(0 0 0 1 1 0 1 1) # 一共只有1中变化(0,0)(0,1)(1,0)(1,1)方块喽
box1=(0 2 1 2 2 2 3 2 1 0 1 1 1 2 1 3) # 一共2种变化(0,2)(1,2)(2,2)(3,2)
box2=(0 0 0 1 1 1 1 2 0 1 1 0 1 1 2 0) # 一共2种变化
box3=(0 1 0 2 1 0 1 1 0 0 1 0 1 1 2 1) # 一共2种变化
box4=(0 1 0 2 1 1 2 1 1 0 1 1 1 2 2 2 0 1 1 1 2 0 2 1 0 0 1 0 1 1 1 2) # 一共4种变化
box5=(0 1 1 1 2 1 2 2 1 0 1 1 1 2 2 0 0 0 0 1 1 1 2 1 0 2 1 0 1 1 1 2) # 一共4种变化
box6=(0 1 1 1 1 2 2 1 1 0 1 1 1 2 2 1 0 1 1 0 1 1 2 1 0 1 1 0 1 1 1 2) # 一共4种变化
#所有其中方块的定义都放到box变量中
box=(${box0[@]} ${box1[@]} ${box2[@]} ${box3[@]} ${box4[@]} ${box5[@]} ${box6[@]})
#各种方块旋转后可能的样式数目
countBox=(1 2 2 2 4 4 4)
#各种方块再box数组中的偏移, 对应可能的样式数量, 这和countBox是一一对应的, 也就是样式最多是15+4为19种
offsetBox=(0 1 3 5 7 11 15)
  
#运行时数据
cBoxNew=0        #新下落的方块的颜色
iBoxNewType=0        #新下落的方块的种类
iBoxNewRotate=0        #新下落的方块的旋转角度
boxCur=()        #当前方块的位置定义
cBoxCur=0        #当前方块的颜色
iBoxCurType=0        #当前方块的种类
iBoxCurRotate=0        #当前方块的旋转角度


#更新新的方块
function RandomBox()
{
        local i j t
 
        #1.随机产生新的方块
        ((iBoxNewType = RANDOM % ${#offsetBox[@]})) # 随机产生方块的类型 [0,7], 这里是大样式, 即7种里面选
        ((iBoxNewRotate = RANDOM % ${countBox[$iBoxNewType]})) # 随机产生方块的角度, 等于是大的样式中里面选择小的样式

        for ((j = 0, i = (${offsetBox[$iBoxNewType]} + $iBoxNewRotate) * 8; j < 8; j++, i++))
        do
        				# j循环8次
        				# i样式索引在数组中的起始位置
                boxNew[$j]=${box[$i]}; #取出方块的定义, 也就是8个点
        done
         ((box_color = ${colorTable[RANDOM % ${#colorTable[@]}]})) #取出随机颜色
        

        #2.显示右边预显示的方块
        echo -ne "\033[1m\033[7m\033[3${box_color}m\033[4${box_color}m" # 设置前景和背景色
        for ((j = 0; j < 8; j += 2))
        do
        				#计算y坐标的计算方式			
        				
                ((i = iTop+ ${boxNew[$j]})) 
                ((t = iLeft+ 2 * ${boxNew[$j + 1]})) #计算x坐标
                echo -ne "\033[${i};${t}HNB" # 坐标绘制
        done
        echo -ne "\033[0m"
}

 
 # RandomBox        #随机产生方块，这时右边预显示窗口中有方快了
 while :
 do 
   clear
      RandomBox        #再随机产生方块，右边预显示窗口中的方块被更新，原先的方块将开始下落
      sleep 1
 done


