
#! /bin/bash
 
 cd "$(cd `dirname $0`; pwd)"		#进入脚步目录
> realtime.txt			#创建文件

put_To_realtime ( )
{

declare -a Name=( 'R1' 'R2' 'C1' 'C2' 'IC1' 'IC2' 'Bga1' 'Bga2' ) #元件名称
let declare -i Count=0 
let declare -i Count_LINE=0 #存放文件名数组的下标
let stop_Record=1 #设置停止记录值，当此值发生变化时，停止记录

test -f realtime.txt && rm realtime.txt ; touch realtime.txt || touch realtime.txt
#表格输入
echo  -en  "Name\tOK(%)\tHEIGTH(MAX)\tHEIGTH(MIN)HEIGTH(Avg)\t" >>realtime.txt
echo  -e >>realtime.txt

#获取输入参数所在目录下的文件名，并至于arr_LINE数组中
for line in $(find ./LINE1 ./LINE2 -type f)  
do    
  arr_LINE[count_LINE]=$line   #arr_LINE为存放目录的数组
  let count_LINE=count_LINE+1  #计数增1

done
#读取每个表格的值放置数组
#先读取所选的元器件，然后在每个表格中读取所选的元器件信息

for var_Name in ${Name[@]}                  #循环读取每个表格的元件名称
do
   #变量声明
  local arr_OK=0
  local arr_total=0
  local arr_SUM=0

  for var in ${arr_LINE[@]}             
  do

    statistics  $var $var_Name            #var为目录参数，var2为元件名称
   # echo $var
    arr_num_OK[Count]=$num_OK             #返回所有OK的个数，存放数组
    arr_total_Number[Count]=$total_Number #返回元件名称总个数，存放数组
    arr_HEIGTH_MAX[Count]=$HEIGTH_MAX     #获取每张表格所得的最大值存放数组
    arr_HEIGTH_MIN[Count]=$HEIGTH_MIN     #获取每张表格所得的最小值存放数组
    arr_HEIGTH_SUM[Count]=$HEIGTH_SUM     #获取每张表格所得的高度总和存放数组
    arr_HEIGTH_Avg[Count]=$HEIGTH_Avg     #获取每张表格所得的高度平均值存放数组
    let Count=Count+1  #=计数增1

  done 

  #把OK total_Number arr_SUM求和
  while [ $Count -ge 0 ]
  do
    let arr_OK=arr_OK+arr_num_OK[Count-1]                              #求ok总和
    let arr_total=arr_total+arr_total_Number[Count-1]                  #求okng总和
    arr_SUM=$(echo "scale=2; ${arr_HEIGTH_SUM[Count-1]}+$arr_SUM" |bc) 
    let Count=Count-1                                                  #计数减1

  done

  #求最小值
  temp_Min=2000
  for var in ${arr_HEIGTH_MIN[@]}
  do
    while [ $(echo "$temp_Min<$var" |bc) -eq 0 ] 
    do
      if [ $(echo "$var==0" |bc) -eq 0 ] #排除表中某个元件名称没有出现的情况
      then
        temp_Min=$var                    #选出最小值
      fi   
      break
    done
  done 

  #求最大值
  temp_Max=${arr_HEIGTH_MAX[0]}
  for var4 in ${arr_HEIGTH_MAX[@]}
  do
    while [ $(echo "$temp_Max>$var4" |bc) -eq 0 ]
    do
      temp_Max=$var4
      break
   done
  done 


let OK=arr_OK*100/arr_total

while [ $OK -lt 30 ] #设置小于阀值，小于某个阀值则输出到表格

do    
local percent_OK=$(echo "scale=2; $arr_OK*100/$arr_total" | bc) #求OK百分比
local HEIGTH_Avg=$(echo "scale=2; $arr_SUM/$arr_total" | bc) #求平均值，scale为保留两位小数

   while [ $stop_Record -eq 1 ]
   do 
     echo  -en "$var_Name  \t" >>realtime.txt
     echo  -en "$percent_OK%\t" >>realtime.txt
     echo  -en "$temp_Max  \t" >>realtime.txt                   	
     echo  -en "$temp_Min  \t" >>realtime.txt
     echo  -e  "$HEIGTH_Avg\t" >>realtime.txt
     let stop_Record=stop_Record+1
     cat realtime.txt #把realtime.txt前两个例输出的屏幕
     break
   done
   break
done 

done
}

################################################################################
#用途:统计每个表格中某个文件名出现的OK值，出现总个数，最大值，最小值以及高度总和
#参数：$1 为文件的位置参数，$2为元件名
#调用方法：statistics+位置参数+元件名
#          如：statistics "./LINE2/170810215732.txt" "R1"
#          表示查找./LINE2/170810215732.txt中的R1元器件信息
#返回值 :TRUE or FALSE
#说明：无
################################################################################

statistics ( ) 

{


num_OK=$(cat $1 | grep $2| grep "OK" | awk '{print $3}' | wc -l)
total_Number=$(cat $1 | grep $2| wc -l)

#防呆，如果某个文件表格中元件个数不为零则计算
#如果某个文件表格中元件个数为零则不计算
if [ $total_Number -ne 0 ]    
then
  #awk'{print $3}'为获取第三列的值，然后排序取出最大最小值
  HEIGTH_MAX=$(cat $1 | grep $2 | awk '{print $3}' | sort -n -r | head -1 )            
  HEIGTH_MIN=$(cat $1 | grep $2 | awk '{print $3}' | sort -n | head -1 )
  HEIGTH_SUM=$(cat $1 | grep $2 | awk '{print $3}' \
                      | awk '{sum += $1};END {print sum}' ) #利用awk求和
 
else                                                                                   
  let HEIGTH_MAX=0  #令最大值为零
  let HEIGTH_MIN=0  #令最小值为零
    percent_OK="0%" #令Ok值为零
  let HEIGTH_Avg=0  #令平均值为零

fi

}


main ( )
{  

    put_To_realtime
    tar -cjf my_LINE.tar.bz2 LINE1/ LINE2/ 

}

main









