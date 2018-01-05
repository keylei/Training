#! /bin/bash

################################################################################
#用途:创建LINE1, LINE2两个目录, 按照当前系统时间每5s创建文件
#参数:无
#返回值:True 或False
#说明：当前目录下创建LINE1, LINE2两个目录, 然后按照当前系统时间每隔5s创建文件
#      文件名的格式根据当前的系统时间决定
################################################################################
create_Files( )
{

#创建文件夹：如过当前文件夹存在则先删除再创建
test  -d LINE1 && rm -rf LINE1 ; mkdir LINE1 || mkdir LINE1  
test  -d LINE2 && rm -rf LINE2 ; mkdir LINE2 || mkdir LINE2  	 
 
#[ -d LINE1 ] &&  rm -rf LINE1 mkdir LINE1  || mkdir LINE1  
#[ -d LINE2 ] && { rm -rf LINE2 mkdir LINE2 } || mkdir LINE2         
#按系统时间每隔5s创建一次文件    
while :
do

  echo -n "."
  local tempDate=$(date "+%g%m%d%H%M%S") #获取当前的系统时间
  touch ./LINE1/"$tempDate.txt" ./LINE2/"$tempDate.txt"
  print "./LINE1/$tempDate.txt"          #调用print函数，并把当前时间作为参数
  print "./LINE2/$tempDate.txt"          #休眠5s
  sleep 5                    																																									
done
   
}

################################################################################
#用途:按格式输出至文本
#参数：$1为文件名，即把文件名传进函数再进行格式化输出
#调用方法：print + 需要输入内容的文件名
#返回值 :TRUE or FALSE
#说明：在生成文本中输入内容文件内容第一行为title, 一共有5列, 
#      分别为ID, Height,Name, Result,NgType和Time
#      每个文件有至少20条记录(具体多少条根据位置参数决定),每个字段以制表符隔开
################################################################################
print ( )
{

local serial_Number=$record_Number #record_Number为全局变量，在main中输入
local temp_Text_Name=$1            #保存变量值

#输入标题，/t为制表符
echo  -en  "ID\tName\tHeight\tResult\tNgType\tTime\t" >>$temp_Text_Name
echo >> $1

#输入随机信息 Table_type返回各种类型名称的随机值
while [ $serial_Number -gt 0 ]
do 
 
  let tSerial_number=record_Number-serial_Number+1 #交换变量,记录当前的ID值
  echo  -en "$tSerial_number\t" >>$temp_Text_Name  #ID值                             	
  echo  -en "$(table_Type 1)\t" >>$temp_Text_Name  #Name
  echo  -en "$(table_Type 2)\t" >>$temp_Text_Name  #Height
  echo  -en "$(table_Type 3)\t" >>$temp_Text_Name  #Result
  echo  -en "$(table_Type 4)\t" >>$temp_Text_Name  #NgType
  echo  -e  "$(table_Type 5)\t" >>$temp_Text_Name  #Time
  let serial_Number-=1                             #总记录条数减1

done 
}

################################################################################
#用途:创建范围[ min , max-1 ] 之间的随机数，即在min 与 max直接获得随机整数
#参数:min max decimal，分别为随机数的最小值及最大值区间及是否需要保留小数点命令
#调用方法：Random min max  decimal
#          如 ：random 2 5 0  表示在2到4之间找随机数
#          数字0表示保留两位小数,1表示只取整数
#          外部程序可以通过temp全局变量获取随机数
#返回值 :TRUE or FALSE
#说明：获得随机数返回值，shell函数里算出随机数后，更新该值
################################################################################

random( )
{
if  [ $3 -le 0 ]
then
  local min=$1;               #定义最小值
  local max=$2-$1;            #定义最大值
  local num=10#$(date +%s%N); #利用系统获得当前时间的纳秒数据，精确到亿分之一秒
  ((retnum=num%max+min));     #进行求余数运算即可

  declare -i t=$3
  local min=1
  local max=100
  local num=10#$(date +%s%N); #利用系统获得当前时间的纳秒数据，精确到亿分之一秒。
  ((retnum2=num%max+min));    #进行求余数运算即可
  temp=$(echo "$retnum2*0.01 +$retnum"|bc) #产生指定范围内的小数,temp为全局变量

else
  local min=$1;
  local max=$2-$1;
  local num=10#$(date +%s%N);#利用系统获得当前时间的纳秒数据，精确到亿分之一秒。
  ((retnum=num%max+min)); #进行求余数运算即可
  temp=$retnum;         
fi
}

#################################################################
#用途:根据输入参数返回所需列表选项
#参数：“1”表示列表“name”选项 
#      “2”表示列表“Hight ”
#      “3”表示列表“Result
#      “4” 表示列表“NgType”
#      “5”表示列表“time”选项
#调用方法：table_Type +相应的菜单列表即可选择相应的列表参数
#返回值 :TRUE or FALSE
#主要命令说明：无
#################################################################

function table_Type ( )
{
if  [ $1 -eq 1 ]  #输入参数“1” 表示列表“name”
then 
        
  random 1 9 1 #调用随机函数1-8，下同
  declare -a Name=( 'R1' 'R2' 'C1' 'C2' 'IC1' 'IC2' 'Bga1' 'Bga2' ) #参数名
  echo  "${Name[temp-1]}" #temp为全局变量，下同

elif  [ $1 -eq 2 ] #输入参数“2”表示列表“Hight选项
then 

  random 300 600 0
  Hight=$temp
  echo  $Hight  
      
elif [ $1 -eq 3 ] #输入参数“3” 表示列表“Result选项
then
 
  random 1 3 1
  declare -a Result=( 'OK' 'NG' ) #参数名
  echo "${Result[temp-1]}"

elif [ $1 -eq 4 ]  #输入参数表示列表“NgType”选项
then
 
  random 1 11 1
  declare -a NgType=( '错料' '偏移' '异物' '桥联' '多锡'\
                      '缺件' '脚翘' '立碑' '翻件' '虚焊' ) #参数名
  echo "${NgType[temp-1]}" 
           
elif  [ $1 -eq 5 ] #输入参数表示列表“time”选项
then
 
  time=$(date +"%F %T")
  echo $time

else

  echo "Then end"

fi
  
}

#################################################################
#用途:判断参数是否合法
#参数：num为输入需要判断的参数
#调用方法：is_LegNumber +输入的参数
#返回值 :0 or 1，数字合法返回0,否则为1
#说明：无
#################################################################
is_LegNumber( )
{

local min_Number=20 #判断数据范围的最小值，最小值可通过此修改
local max_Number=50 #判断数据范围的最大值，最大值可通过此修改
local num=$1        #获取输入变量的值

if [ "$num" -gt 0 ] 2>/dev/null 
then 

   if [ $num -lt $min_Number ]   #输入的参数小于阀值，输出提示信息
   then
     echo  "输入的数字过小，请重新输入！" 
     return 1

   elif [ $num -gt $max_Number ] #输入的参数大于阀值，输出提示信息
   then
     echo "输入的数字过大，请重新输入！"
     return 1

   else     
    return 0
   
   fi

else
   echo "输入的字符非法，请重新输入" #输入其他非字符，输出提示信息
   return 1

fi
}


#################################################################
#用途:主程序入口
#参数：无
#调用方法：无
#返回值 :无
#说明：无
#################################################################
main ( )
{

#输入数字判断
let num=1                      #变量声明
while [ $num -ne 0 ] 
do
echo -n "请输入位置记录数目(20-50之间)："
read record_Number
is_LegNumber $record_Number      #记录时间
num=$?                        #记录上条命令的函数返回值
done

while [ $num -eq 0 ]          #位置参数合法则执行 
do
  create_Files &              #后台运行
  get_Pid=$!                  #获取 create_Filesid
  echo -n "正在创建文件，请按"y"停止创建 ..."


  while :
  do 
    read  input 
    while [ "$input" == "y" ] 
    do               
      kill $get_Pid >/dev/null 2>&1 #如果输入字符为“y”,停止创建文件
      echo "停止创建文件"
      break

    done 
    break
  done

break
done 
}
main

