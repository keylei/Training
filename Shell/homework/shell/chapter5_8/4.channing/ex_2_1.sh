#! /bin/bash


################################################################################
#用途:把LINE1和LINE2的所有文件名(不包含扩展名)输出到cad.txt文件中, 每行一个
#参数：LINE 表示当前的文件名
#调用方法：put_Content_Tocad
#返回值 :TRUE or FALSE
#说明：无
################################################################################
put_Content_Tocad ( )
{

test -f cad.txt && rm cad.txt ; touch cad.txt || touch cad.txt #创建文件
let declare -i count_LINE=0 #porc文件数量  

#把LINE1，LINE2目录下的文件放置数组arr_LINE
for line in $(find ./LINE1 ./LINE2 -type f)  
do  
  arr_LINE[count_LINE]=$line   #记录当前读取的文件名
  let count_LINE=count_LINE+1  #计数增1

done
echo "===============以下为输出LINE1和LINE2的文件名信息===============">>cad.txt
for var in ${arr_LINE[@]}
do

   echo ${var%.*} >>cad.txt #去除后缀名并存放至cad.txt
   
done
echo "===============以上为输出LINE1和LINE2的文件名信息===============">>cad.txt
echo >>cad.txt
echo >>cad.txt

}
 
put_StaTocad ( )
{

declare -a Name=( 'R1' 'R2' 'C1' 'C2' 'IC1' 'IC2' 'Bga1' 'Bga2' ) #定义元件名称
let declare -i count_LINE=0 

#表格标题输入
echo "=================以下为输出各个元器件的统计信息=================">>cad.txt
echo  -en  "Name\tOK(%)\tHEIGTH(MAX)\tHEIGTH(MIN)HEIGTH(Avg)\t" >>cad.txt
echo  -e >>cad.txt

#获取输入参数所在目录下的文件名，并至于arr_LINE数组中
for line in $(find ./LINE1 ./LINE2 -type f)  
do    
  arr_LINE[count_LINE]=$line   #arr_LINE为存放目录的数组
  let count_LINE=count_LINE+1  #计数增1

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
  local percent_OK=$(echo "scale=2; $arr_OK*100/$arr_total" | bc) #求OK百分比
  local HEIGTH_Avg=$(echo "scale=2; $arr_SUM/$arr_total" | bc) #求平均值
  echo  -en "$var_Name\t" >>cad.txt                            #存放元器件名称
  echo  -en "$percent_OK%\t" >>cad.txt                         #存放元器件ok率
  echo  -en "$temp_Max \t" >>cad.txt                           #存放元器件最大值                   	
  echo  -en "$temp_Min \t" >>cad.txt                           #存放元器件最小值
  echo  -e  "$HEIGTH_Avg\t" >>cad.txt                          #存放元器件平均值
done
echo "=================以上为输出各个元器件的统计信息=================">>cad.txt
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
case_Search ( )
{


local stop_Search="y"
while [ $stop_Search = "y" ]
do
  echo "请输入元件的名称选择输出相应OK(%)率 : "
  read input_Key
  echo -n "$input_Key的OK(%)率是:$num" #num为
  ##防呆##
  case $input_Key in
    "R1") echo $(cat cad.txt | grep R1   | awk '{print $2}') ;;  
    "R2") echo $(cat cad.txt | grep R2   | awk '{print $2}') ;;  
    "C1") echo $(cat cad.txt | grep C1   | awk '{print $2}') ;;        
    "C2") echo $(cat cad.txt | grep C2   | awk '{print $2}') ;;  
   "IC1") echo $(cat cad.txt | grep IC1  | awk '{print $2}') ;;       
   "IC2") echo $(cat cad.txt | grep IC2  | awk '{print $2}') ;;  
  "Bga1") echo $(cat cad.txt | grep Bga1 | awk '{print $2}') ;;  
  "Bga2") echo $(cat cad.txt | grep Bga1 | awk '{print $2}') ;;  
       *) echo "输入有误，请重新输入";;    
  esac
  echo "是否继续查询？请输入“y”继续，输入其他字符退出查询"
  read stop_Search
 
done 
echo "已退出查询"  

}


main ( )
{
   put_Content_Tocad
   put_StaTocad
   case_Search
}
main

 
