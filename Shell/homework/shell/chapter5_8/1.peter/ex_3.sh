 #! /bin/bash
 
#=============================================================================
#3. 创建一个脚本, 统计最近生产信息
#   -脚本接受一个参数, 参数往前进行统计的时间数. 如输入5, 就是往前推5s, 10就是10s
#   -根据输入的时间生成统计时间范围到search.txt文档, 如
#    2010-02-27 11:29:52 - 2010-02-27 11:29:57
#   -根据时间统计表1中TIME满足要求的所有元件, 这张表生成类似与表1, 到search.txt
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
elif [ $1 -lt 0 ]			#判断参数是否在区间内
then
  echo "Error! Please input the number big than 0!" ; exit 1
fi

#覆盖文件
> search.txt				

declare ofPath=search.txt		#输出文件:output file Path
declare headerArray=('ID' 'Name' 'Height' 'Result' 'NgType' 'Time')

backTime=$1				#输入时间区间,以当前时间前推
endTime=$(date +%s)			#获得当前时间作为结束时间
startTime=$[$[endTime]-$[backTime]]	#通过backTime获得开始时间

#提示信息:搜索数据信息
echo "Search data , Please wait ..."

#打印要搜索的时间区间:startTime-endTime
echo -e "Time interval:" >> $ofPath
echo `date -d "@$[startTime]" "+%F %T"` - `date -d "@$[endTime]" "+%F %T"`\
               >> $ofPath
echo >> $ofPath

for var in ${headerArray[@]}		#输入数据表头
do
  printf "%-12s" $var >> $ofPath	#将表头写入文件,左对齐,间隔12个字符
done
echo >> $ofPath				#空行,排版文件

newID=1					#搜索到的文件添加新ID号
#查找所有文件轮寻,并搜索指定时间内的数据
for fileName in $(find "./Line1/" "./Line2/" -type f -name "*.txt" )
do
  while read  col1 col2 col3 col4 col5 col6
  do
    #第一列不是"ID"字符则比较第六列的时间是否大于等于开始时间
    if [ "${col1}" != "ID" ] && [ $(date +%s -d "$col6") -ge $startTime ]
    then
      #更改ID号,并连同ID号和其他数据写入文件,左对齐,间隔12个字符
      printf "%-12s%-12s%-12s%-12s%-12s%-12s\n" \
      		$newID $col2 $col3 $col4 $col5 "$col6" >> $ofPath
      let newID++
    fi
  done < "$fileName"
done
echo "Finish"

exit 0
