#! /bin/bash

#==============================================================================
#  1、俄罗斯方块颜色随机显示
#  2、俄罗斯方块形状随机显示
#  3、每隔1秒更新一次形状与颜色
#==============================================================================

#定义所有形状的坐标
box0=(0 0 1 0 0 1 1 1)
box1=(0 0 1 0 2 0 3 0)
box2=(0 0 0 1 0 2 0 3)
box3=(0 0 1 0 1 1 2 1)  
box4=(1 0 0 1 1 1 0 2)
box5=(1 0 2 0 0 1 1 1) 
box6=(0 0 0 1 1 1 1 2)
box7=(0 0 0 1 1 1 2 1)  
box8=(0 0 1 0 0 1 0 2)  
box9=(0 0 1 0 2 0 2 1)  
box10=(1 0 1 1 0 2 1 2)
box11=(2 0 0 1 1 1 2 1)
box12=(0 0 0 1 0 2 1 2)  
box13=(0 0 1 0 2 0 0 1)  
box14=(0 0 1 0 1 1 1 2)
box15=(1 0 0 1 1 1 2 1)  
box16=(0 0 0 1 1 1 0 2)  
box17=(0 0 1 0 2 0 1 1)  
box18=(1 0 0 1 1 1 1 2)

boxTypeCnt=18 #总共有18中颜色

#设置背景颜色,光标控制等属性
     black=$'\033[40m\033[1m'
       red=$'\033[41m\033[1m'
     green=$'\033[42m\033[1m'
    yellow=$'\033[43m\033[1m'
      blue=$'\033[44m\033[1m'
   magenta=$'\033[45m\033[1m'
      cyan=$'\033[46m\033[1m'
     white=$'\033[47m\033[1m'
    normal=$'\033[0m'
hideCursor=$'\033[?25l'
#数组:背景颜色
colorArray=($black $red $green $yellow $blue $magenta $cyan $white)

#函数:随机生成自定义区间的整数
random ()
{
  local min=$1					#输入参数:最小值
  local max=$2					#输入参数:最大值
  nanoSec=10#$(date +%N)			#获得10进制纳秒数
  randSec=$((nanoSec%($max-$min+1)+$min))	#获得自定义区间的随机数
  echo $randSec
}

while true
do
  clear						#清屏
  left=3				#左侧空3列
  top=2					#顶部空2行 
  
  #box数组一共19个,分别是box0到box18;color数组一共8个元素,索引从[0-7]
  (( boxIndex=$(random 0 $boxTypeCnt) ))			#在[0-18]中随机获得形状的索引
  (( colorIndex=$(random 0 ${#colorArray[*]}) ))		#在[0-7]中随机获得颜色的索引
  
  #eval后的参数在shell中将扫描两次
  #第一次将\$替换为$,${boxIndex}替换为上面获得的索引,如:${box5[@]}
  #第二次将第一次获扫描获得的${box5[@]}赋给数组boxShape
  eval boxShape=(\${box${boxIndex}[@]})		#将获得的形状赋给boxShape
  echo -e ${colorArray[$colorIndex]}		#设置方块颜色

  for (( i=0;i<${#boxShape[@]};i+=2 ))	
  do						#遍历数组中组成图像的4对坐标
    (( x = left + 2*${boxShape[i]} ))	#x坐标位置,打印n个字符参数前就乘以n
    (( y = top + ${boxShape[i+1]} ))	#y坐标位置

    echo -e "\033[${y};${x}H  "			#将自定义字符打印在当前坐标,两个空格
  done
  echo -e $normal$hideCursor			#恢复默认颜色.隐藏光标 
  sleep 1
done




