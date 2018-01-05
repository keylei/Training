#! /bin/bash


################################################################################
#用途:把LINE1和LINE2的所有文件名(不包含扩展名)输出到cad.txt文件中, 每行一个
#参数：LINE 表示当前的文件名
#调用方法：put_Content_Tocad
#返回值 :TRUE or FALSE
#说明：无
################################################################################
put_Content_To_ngType ( )
{

test -f ngType.txt && rm ngType.txt ; touch ngType.txt || touch ngType.txt #创建文件
let declare -i count_LINE=0 #porc文件数量  

#把LINE1，LINE2目录下的文件放置数组arr_LINE
for line in $(find ./LINE1 ./LINE2 -type f)  
do  
  arr_LINE[count_LINE]=$line   #记录当前读取的文件名
  let count_LINE=count_LINE+1  #计数增1

done
echo "==============以下为输出LINE1和LINE2的文件名信息=============">>ngType.txt
for var in ${arr_LINE[@]}
do

   echo ${var%.*} >>ngType.txt #去除后缀名并存放至cad.txt
   
done
echo "==============以上为输出LINE1和LINE2的文件名信息=============">>ngType.txt
echo >>ngType.txt
echo >>ngType.txt

}
################################################################################
#用途:根据LINE1和LINE2中所有的数据生成一张表
#     统计在NG的元件中各个NgType所占的比例,输出到ngtype.txt
#参数：
#调用方法：put_Content_Tocad
#返回值 :TRUE or FALSE
#说明：无
################################################################################
put_Sat_To_ngType ( )
{

declare -a Name=( '错料' '偏移' '异物' '桥联' '多锡' '缺件'\
                  '脚翘' '立碑' '翻件' '虚焊' ) #NgType类型

let declare -i Count_LINE=0 
echo "================以下为输出各个元器件的统计信息===============">>ngType.txt
#表格输入
echo  -en  "NgType\t">>ngType.txt
echo  -e   "Ng(%)\t" >>ngType.txt

#获取输入参数所在目录下的文件名，并至于arr_LINE数组中
#如：$1为LINE1目录，$2为LINE2目录
for line in $(find ./LINE1 ./LINE2 -type f)  
do 
     
  arr_LINE[Count_LINE]=$line   #arr_LINE为存放目录的数组
  let Count_LINE=Count_LINE+1  #计数增1

done

#读取每个表格的值放置数组
#先读取所选的元器件，然后在每个表格中读取所选的元器件信息
let declare -i Count=0 

for var_Name in ${Name[@]}                  #循环读取每个表格的元件名称
do
  #变量声明
  local arr_OK=0
  local arr_total=0
  local arr_SUM=0


  for var in ${arr_LINE[@]}             
  do

    statistics  $var $var_Name            #var为目录参数，var2为元件名称
    arr_num_OK[Count]=$num_OK             #返回所有OK的个数，存放数组
    arr_total_Number[Count]=$total_Number #返回元件名称总个数，存放数组
    let Count=Count+1  #=计数增1

  done 

#把OK total_Number求和
while [ $Count -ge 0 ]
do
  
  let arr_OK=arr_OK+arr_num_OK[Count-1]
  let arr_total=arr_total+arr_total_Number[Count-1]
  let Count=Count-1 #计数减1

done

local percent_OK=$(echo "scale=2; $arr_OK*100/$arr_total" | bc) #求OK百分比
echo  -en "$var_Name  \t">>ngType.txt
echo  -e  "$percent_OK%\t">>ngType.txt

done
echo "================以上为输出各个元器件的统计信息===============">>ngType.txt
}

#################################################################
#用途:统计每个表格中某个文件名出现的OK值，出现总个数，最大值，最小值以及高度总和
#参数：$1 为文件的位置参数，$2为元件名
#调用方法：statistics+位置参数+元件名
#          如：statistics "./LINE2/170810215732.txt" "R1"
#          表示查找./LINE2/170810215732.txt中的R1元器件信息
#返回值 :TRUE or FALSE
#说明：无
#################################################################

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


#################################################################
#用途:支持使用select, 通过选择NgType来输出相应的OK(%)
#参数：无
#调用方法：select_Search
#返回值 :TRUE or FALSE
#说明：无
#################################################################
select_Search ( )
{
declare -a NgType=(  '错料' '偏移' '异物' '桥联' '多锡' '缺件' '脚翘' '立碑' '翻件' '虚焊' ) #NgType
echo "请输入元件的名称选择输出相应OK(%)率 (按CTRL+C退出查询): "
select input_Key in ${NgType[@]} 
do
  case $input_Key in
    "错料") echo $(cat ngType.txt | grep 错料 | awk '{print $2}') ;;  
    "偏移") echo $(cat ngType.txt | grep 错料 | awk '{print $2}') ;;  
    "异物") echo $(cat ngType.txt | grep 异物 | awk '{print $2}') ;;  
    "桥联") echo $(cat ngType.txt | grep 桥联 | awk '{print $2}') ;;        
    "多锡") echo $(cat ngType.txt | grep 多锡 | awk '{print $2}') ;;  
    "缺件") echo $(cat ngType.txt | grep 缺件 | awk '{print $2}') ;;       
    "脚翘") echo $(cat ngType.txt | grep 脚翘 | awk '{print $2}') ;;  
    "立碑") echo $(cat ngType.txt | grep 立碑 | awk '{print $2}') ;;  
    "翻件") echo $(cat ngType.txt | grep 翻件 | awk '{print $2}') ;;  
    "虚焊") echo $(cat ngType.txt | grep 立碑 | awk '{print $2}') ;;
     *)
       echo "输入有误，请重新输入";;    

esac
done

}

main ( )
{
   put_Content_To_ngType 
   put_Sat_To_ngType
   select_Search
}
main
