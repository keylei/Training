#! /bin/bash

#==============================================================================
#1.创建一个进程, 生成数据
#   1.1 当前目录下创建LINE1, LINE2两个目录, 然后按照当前系统时间每隔5s创建文件, 
#      文件名的格式根据当前的系统时间决定, 如:
#      ├── Line1
#      │   ├── 170808153146.txt
#      │   └── 170808153151.txt
#      └── Line2
#          ├── 170808153146.txt
#          └── 170808153151.txt
#  1.2 文件内容第一行为title, 一共有5列, 分别为ID, Height,Name, Result,NgType
#      和Time, 每个文件有至少20条记录(具体多少条根据位置参数决定),每个字段以制
#      表符隔开, 文件内容的具体格式如下:
#
#      **表1**
#      ID	Name	Height  Result	NgType	Time
#      1	R1	500     NG	偏移	2010-02-27 11:29:52
#      2	R2	600     OK	偏移	2010-02-27 11:32:52
#
#     **字段&说明**
#     ID:直接代表了行数, 从1开始, 顺序变大
#     Height:300-600 随机生成, 保留小数点2位
#     Name | 从"R1,R2,C1,C2,IC1,IC2,Bga1,Bga2"中随机选取
#     Result | 不是OK,就是NG, 随机决定
#     NgType | 从"错料 偏移 异物 桥联 多锡 缺件 脚翘 立碑 翻件 虚焊"随机选取
#     Time | 按照上述格式输出时间戳
#
#     **Note**:
#     > 输入的位置参数需要进行防呆, 最少20条, 但也不能太大
#==============================================================================

if [ $# -ne 1 ]						#判断参数是否是一个
then
  echo "Error! Please input one argument!" ; exit 1
elif [ "$( echo $1 | bc 2>/dev/null )" != "$1" ]	#判断参数是否是数字
then
  echo "Error! Please input a digit!" ; exit 1
elif echo $1 | grep "\." >/dev/null 2>&1		#判断参数是否是整数
then 
  echo "Error! Please input an interger" ; exit 1
elif [ $1 -lt 20 ] || [ $1 -gt 100 ]			#判断参数是否在区间内
then
  echo "Error! The number between 20 and 100!" ; exit 1
fi

#声明Name、Result、NgType、header数组变量
declare headerArray=('ID' 'Name' 'Height' 'Result' 'NgType' 'Time')
declare NameArray=('R1' 'R2' 'C1' 'C2' 'IC1' 'IC2' 'Bga1' 'Bga2')
declare ResultArray=('NG' 'OK')
declare NgTypeArray=('错料' '偏移' '异物' '桥联' '多锡'\
		     '缺件' '脚翘' '立碑' '翻件' '虚焊')
#目录不存在则创建
[ ! -d Line1 ] && mkdir Line1				
[ ! -d Line2 ] && mkdir Line2

#函数：获得自定义区间的随机数函数,函数名称后面加最小值最大值精度,以空格分隔
random ()
{
  local min=$1			#定义局部变量:最小值
  local max=$2			#定义局部变量:最大值
  local precision=$3		#定义局部变量:小数点精度位数
  local divisor=1		#定义局部变量：除数

  while [ $precision -gt 0 ]	#通过while循环将小数变为整数,同时增大除数
  do
    let precision--		#精度位数降低
    let min*=10			#最小值乘10
    let max*=10			#最大值乘10
    let divisor*=10		#除数乘10
  done

  nanoSec=10#$(date +%N)				#获取十进制纳秒数
  randSec=$((nanoSec%($max-$min+1)+$min))		#获取指定范围的随机数
  echo $(echo "scale=$3; $randSec/$divisor" | bc)
}

#函数：通过随机函数random输出数据,函数名称后加输出到的文件路径
printData()
{
  local filePath=$1
  echo -en "$i\t" >> $filePath					#写入ID号
  echo -en "${NameArray[$(random 0 7 0)]}\t" >> $filePath	#写入Name
  echo -en "$(random 300 600 2)\t" >> $filePath			#写入Height
  echo -en "${ResultArray[$(random 0 1 0)]}\t" >> $filePath	#写入Result
  echo -en "${NgTypeArray[$(random 0 9 0)]}\t" >> $filePath	#写入NgType
  echo -en "$(date "+%F %T")\t\n" >> $filePath			#写入Time
}

#函数：创建目录及文件，并写入数据
createData()
{
  local dataCnt=$1			#输入参数：单文件中写入数据的数量
  
  while true
  do
    name="$(date "+%y%m%d%H%M%S").txt"	#文件格式：170808153621.txt
    touch ./Line1/$name ./Line2/$name	#在Line1、Line2目录下生成文件

    for var in ${headerArray[@]};	#通过遍历标题数组,生成标题名称
    do
     echo -en "$var\t" >> ./Line1/$name	#写入标题
     echo -en "$var\t" >> ./Line2/$name
    done
    echo >> ./Line1/$name		#换行,控制输出文件排版
    echo >> ./Line2/$name

    for (( i=1;i<=$dataCnt;i++ ))	#根据输入参数生成数据
    do
      printData ./Line1/$name		#将数据写入新建的文件中
      printData ./Line2/$name 
    done
    
    sleep 5				#每隔5s循环一次
  done
}

createData $1 &				#将传入的参数传给createData并后台运行
createDataPid=$!			#获取后台进程的PID

while true				#退出
do
  echo -e  "Create file and data!"
  echo -en "Enter \"y\" to stop:"
  read enterPress
  if [ "$enterPress" == "y" ]
  then 
    break
  fi
done
echo "Please wait to finish creating!"
sleep 2					#sleep两秒等待数据写完
kill $createDataPid >/dev/null 2>&1	#kill后台进程并退出
echo "Finish!"

exit 0
