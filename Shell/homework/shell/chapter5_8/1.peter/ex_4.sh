#! /bin/bash

#==============================================================================
#4.创建一个间隔为一分钟的后台定时任务
#  -总是统计所有元件的OK/NG情况, 当有任何一个元件的OK%低于30%时, 生成一张类似与
#   2的表格到realtime.txt(只有一条记录, 即第一次触发该条件的元件)
#
#   **表4**
#   Name	OK(%)  	HEIGTH(MAX)    HEIGTH(MIN)      HEIGTH(Avg)	    
#   R1		20%     600             400	        450
#
#  -把realtime.txt前两个例输出的屏幕
#  -把LINE1和LINE2所有数据按照其目录结构进行bzip2压缩备份
#==============================================================================

cd "$(cd `dirname $0`; pwd)"		#进入脚步目录
> realtime.txt			#创建文件

declare ofPath=realtime.txt	#输出文件 output file path
declare titleArray=( 'Name' 'OK(%)' 'HEIGTH(MAX)' 'HEIGTH(MIN)' 'HEIGTH(Avg)')
declare chipNameArray=('R1' 'R2' 'C1' 'C2' 'IC1' 'IC2' 'Bga1' 'Bga2')
fileList="$(find "./Line1/" "./Line2/" -type f -name "*.txt")"

#打印标题信息
echo "=======================第一个OK率低于30%的元件=========================" \
	>> $ofPath
for title in ${titleArray[@]}		#遍历信息标题
do 
  printf "%-15s" $title >> $ofPath	#打印标题，左对齐，间隔15个字符
done

echo >> $ofPath				#换行,文件排版

#遍历每种元件名称,统计OK率和高度信息      
for var in ${chipNameArray[@]}
do
  heightAvg=0.00
  #获得目标元件个数和目标元件中ok的个数
  goalCnt=$(awk '{if ($2=="'$var'") print $0}' $fileList | wc -l)
  okCnt=$(awk '{if ($2=="'$var'" && $4=="OK") print $0}' $fileList | wc -l)
  #获取Ok的元件高度并从小排序存入数组
  heightArray=($(awk '{if ($2=="'$var'" \
  		&& $4=="OK") print $3}' $fileList | sort -n ))
  #轮寻数组求高度的和
  for height in ${heightArray[@]}
  do 
    heightAvg=$(echo "$height $heightAvg" | awk '{printf "%.2f\n",$1+$2}')
  done
  
  #目标元件的OK率
  value="$(echo "$okCnt $goalCnt" | awk '{printf "%.2f",100*$1/$2}')"

  #判断value是否小于30%,是则打印数据到文件中
  if [ `echo "$value<=50" | bc` -eq 1 ]
  then
    #写入目标名称
    printf "%-15s" $var >> $ofPath
    #写入ok的比率
    printf "%-15s" $(echo "$okCnt $goalCnt" | \
    		awk '{printf "%.2f",100*$1/$2}')% >> $ofPath
    #写入最大值
    printf "%-15s" ${heightArray[${#heightArray[*]}-1]} >> $ofPath
    #写入最小值
    printf "%-15s" ${heightArray[0]} >> $ofPath
    #写入平均值
    printf "%-15s" $(echo "$heightAvg $okCnt" |\
    		 awk '{printf "%.2f",$1/$2}') >> $ofPath
    
    break
  fi
done

#以当前时间创建要压缩的文件名
name="$(date "+%y%m%d%H%M%S").tar.bz2"

#按时间格式压缩目录中所有文件
tar -cjf "$name" Line1/ Line2/

exit 0
