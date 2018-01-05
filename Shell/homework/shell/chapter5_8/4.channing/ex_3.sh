#! /bin/bash


################################################################################
#用途:脚本接受一个参数, 参数往前进行统计的时间数. 输入5, 就是往前推5s, 10就是10s
#参数：无
#调用方法：transfor_Time
#返回值 :TRUE or FALSE
#说明：无
################################################################################

transfor_Time( )
{

#输入数字判断
let num=1                      #变量声明
while [ $num -ne 0 ] 
do
echo -n "请输入需要前进的时间：(单位：秒) "
read record_Number
is_Number $record_Number      #记录时间
num=$?                        #记录上条命令的函数返回值
done

#创建文件
test -f search.txt && rm search.txt ; touch search.txt || touch search.txt 

while [ $num -eq 0 ]          #位置参数合法则执行 
do
  local CURTIME=$(date +"%Y-%m-%d %H:%M:%S") #当前的系统时间
  time2=$(date +%s -d "$CURTIME")  #将当前的系统时间为时间戳
  tfor_time=$(($time2-$record_Number)) #前进的时间
  time1=$(date +%Y-%m-%d\ %H:%M:%S -d "1970-01-01 UTC $tfor_time seconds");
  echo "时间差为："                                       >>search.txt
  echo "==========================================================" >>search.txt
  echo "$time1 - $CURTIME"                                >>search.txt
  echo "==========================================================" >>search.txt

break
done

}

read_FileTime ( )
{

#获取获取LINE1/LINE2下所有文本的名称，并存放arr_LINE数组中
let Count_Title=0
for line in $(find ./LINE1 ./LINE2 -type f)  
do 
     
  arr_LINE[Count_Title]=$line 
  let Count_Title=Count_Title+1  #计数增1

done

#创建文件并填写标题

echo "==================以下为时间差所查询到的数据================" >>search.txt
echo  -en  "ID\t Name\t Height\tResult\t NgType\t">>search.txt
echo  -e   "Time\t">>search.txt


#获取LINE1/LINE2下所有文本表格的时间,并存在arr_time中
let Count_Times=0
for var in ${arr_LINE[@]}
do

  while  read -r f1 f2 f3 f4 f5 f6
  do
    while [ "$f6" != "Time" ]
    do

      time=$(date +%s -d "$f6")
      
      
      while [ $time -ge $tfor_time ]
      do
        let Count_Times=Count_Times+1
        echo -en "$Count_Times\t $f2\t $f3\t  $f4\t  $f5\t">>search.txt
        echo -e  "  $f6\t" >>search.txt
        break

      done
      break

    done
  done  < $var

done 
}

#################################################################
#用途:判断参数是否是数字
#参数：num为输入需要判断的参数
#调用方法：is_LegNumber +相应的数字参数
#返回值 :TRUE or FALSE
#主要命令说明：无
#################################################################
is_Number( )
{

if [ "$1" -gt 0 ] 2>/dev/null 
then 
 
   return 0
else 
   echo "输入的字符非法，请重新输入" 
   return 1
fi
}
main ( )
{   
     transfor_Time
     read_FileTime
}

main





