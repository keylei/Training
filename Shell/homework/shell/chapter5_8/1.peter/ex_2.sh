#! /bin/bash

#==============================================================================
#2.创建一个脚本, 进行统计
#  2.1 在当前目录下生成一张cad.txt文档
#     -把LINE1和LINE2的所有文件名(不包含扩展名)输出到cad.txt文件中, 每行一个
#     -根据LINE1和LINE2中所有的数据生成一张表输出到cad.txt, 生成如下的表
#     -使用case, 通过选择元件的Name来输出相应的OK(%)
#
#     **表2**
#     Name	OK(%)  	HEIGTH(MAX)    HEIGTH(MIN)      HEIGTH(Avg)	    
#     R1	70%     600             400	        450
#     R2	30%     590             323	        400
#
#     **字段&说明**
#     Name:在1中所有出现的元件(R1,R2,C1,C2,IC1,IC2,Bga1,Bga2)的名称
#     OK(%):计算该元件总体的OK的百分比
#     HEIGTH(MAX):计算该元件高度的最大值(保留小数点2位)
#     HEIGTH(MIN):计算该元件高度的最小值(保留小数点2位)
#     HEIGTH(Avg):计算该元件高度的平均值
#
#     **Note**:
#     > 需要把LINE1和LINE2所有出现的元件全部统计在内
#
#  2.2 在当前目录下生成一张ngType.txt文档
#      -把LINE1和LINE2的所有文件名(不包含扩展名)输出到ngType.txt文件中, 每行一个
#      -根据LINE1和LINE2中所有的数据生成一张表, 统计在NG的元件中各个NgType所占的
#       比例,输出到ngtype.txt
#      -支持使用select, 通过选择NgType来输出相应的OK(%)
#
#      **表3**
#      NgType	Ng(%)  	 
#      偏移	70%                	        
#      异物	20%   
#
#      **Note**:
#      > 需要把所有的Ng类型统计在内, Ng(%)为所有在Ng的元件中各个NgType占有的比例
#==============================================================================

#覆盖文件
> cad.txt
> ngType.txt

#定义数组
declare titleArray=( 'Name' 'OK(%)' 'HEIGTH(MAX)' 'HEIGTH(MIN)' 'HEIGTH(Avg)' )
declare chipNameArray=('R1' 'R2' 'C1' 'C2' 'IC1' 'IC2' 'Bga1' 'Bga2')
declare ngTypeArray=('错料' '偏移' '异物' '桥联' '多锡'\
                     '缺件' '脚翘' '立碑' '翻件' '虚焊')
#获得所有文件路径,存放如fileList数组
fileList=($(find "./Line1/" "./Line2/" -type f -name "*.txt"))

#函数：搜索文件并输出文件名到目标文件中,函数名称后面加输入输出路径
printFileName()
{
  local inpath=$1				#输入路径
  local outPath=$2				#输出路径
  echo -en "文件路径:$inpath\n" >> $outPath	#将目录路径写入到文件
  for i in ${fileList[@]##*/}			#去除文件路径
  do
    echo ${i%.*} >> $outPath      		#去除文件后缀，并写入文件
  done
  echo >> $outPath				#输出空行,将文件排版
}

#生成cat.txt和ngType.txt并写入数据
printFileName ./Line1/ cad.txt		#搜索文件，写入到cad.txt中
printFileName ./Line2/ cad.txt
printFileName ./Line1/ ngType.txt	#搜索文件，写入到ngType.txt中
printFileName ./Line2/ ngType.txt

#写入元件信息标题
for var in ${titleArray[@]}		#遍历信息标题
do 
  printf "%-15s" $var >> cad.txt	#打印标题，左对齐，间隔15个字符
done
echo >> cad.txt				#输出空行,将文件排版

for okvar in ${chipNameArray[@]}		#遍历元件名称数组,获得其ng等信息
do
  heightAvg=0
  
  #通过awk遍历fileList,查找第二列为当前名称的元件,统计总数和元件中ok的个数
  goalChipCnt=$(awk '{if ($2=="'$okvar'") print $0}' $fileList | wc -l)
  okChipCnt=$(awk '{if ($2=="'$okvar'" && $4=="OK") print $0}' $fileList | wc -l)

  #遍历数组,查找目标元件中OK的元件,并按照高度排序然后存入数组
  heightArray=($(awk '{if ($2=="'$okvar'" \
               && $4=="OK") print $3}' $fileList | sort -n ))  
  
  #轮寻目标数组,求所有符合元件的高度的总和
  for height in ${heightArray[@]}
  do 
    heightAvg=$(echo "$height $heightAvg" | awk '{printf "%.2f",$1+$2}')
  done
  
  #目标元件的OK率
  value="$(echo "$okChipCnt $goalChipCnt" | awk '{printf "%.2f",100*$1/$2}')"
  
  #写入目标元件名称到文件中,左对齐,间隔15个字符
  printf "%-15s" $okvar >> cad.txt
  
  #写入ok的比率:通过元件个数及其中的OK的个数比值算出OK率
  printf "%-15s"  ${value}% >> cad.txt

  #写入最大值:OK元件heightArray数组的最后一位
  printf "%-15s" ${heightArray[${#heightArray[*]}-1]} >> cad.txt
  #写入最小值:数组第一位
  printf "%-15s" ${heightArray[0]} >> cad.txt
  #写入平均值:通过元件高度总和除以元件个数,保留两位小数
  printf "%-15s\n" $(echo "$heightAvg $okChipCnt" \
                   | awk '{printf "%.2f",$1/$2}') >> cad.txt
done

#统计元件NgType百分比
ngChipCnt=$(awk '{if($4=="NG") print $4}' $fileList | wc -l)

#打印标题并写入ngType.txt 
echo -e "NgType       Ng(%)" >> ngType.txt

#轮寻ngTypeArray数组,将每种ngType数据统计并写入到ngType.txt
for ngvar in ${ngTypeArray[@]}
do 
  goalNgChipCnt=$(awk '{if($4=="NG" &&\
                $5=="'$ngvar'") print $5}' $fileList | wc -l)
  printf "%-15s%-15s\n" $ngvar $(echo "$goalNgChipCnt $ngChipCnt" \
                       | awk '{printf "%.2f",100*$1/$2}')% >> ngType.txt
done

#用户交互
okTypePrint()
{
    while true
    do 
      echo  "1)R1      3)C1      5)IC1     7)Bga1    9)Exit"
      echo  "2)R2      4)C2      6)IC2     8)Bga2"
      echo  "==============Please choice ICType=============="; read choice
      case "$choice" in
      1)
        grep -w "R1" cad.txt | awk '{print $1,$2}' 
        ;;
      2) 
        grep -w "R2" cad.txt | awk '{print $1,$2}' 
        ;;
      3)
        grep -w "C1" cad.txt | awk '{print $1,$2}' 
        ;;
      4)
        grep -w "C2" cad.txt | awk '{print $1,$2}' 
        ;;
      5)
        grep -w "IC1" cad.txt | awk '{print $1,$2}' 
        ;;
      6)
        grep -w "IC2" cad.txt | awk '{print $1,$2}' 
        ;;
      7)
        grep -w "Bga1" cad.txt | awk '{print $1,$2}' 
        ;;
      8)
        grep -w "Bga2" cad.txt | awk '{print $1,$2}' 
        ;;
      9)
        break
        ;;
      *)
        echo "Error!Please choice number 1-9!"
     esac
     echo
   done
}

ngTypePrint()
{
  PS3="=================Please choice NGType================="
  echo
  select choice in 错料 偏移 异物 桥联 多锡 缺件 脚翘 立碑 翻件 虚焊 返回
  do 
    case $choice in 
    错料)
      grep -w "错料" ngType.txt | awk '{print $1,$2}'
      ;;
    偏移)
      grep -w "偏移" ngType.txt | awk '{print $1,$2}'
      ;;
    异物)
      grep -w "异物" ngType.txt | awk '{print $1,$2}'
      ;;
    桥联)
      grep -w "桥联" ngType.txt | awk '{print $1,$2}'
      ;;
    多锡)
      grep -w "多锡" ngType.txt | awk '{print $1,$2}'
      ;;
    缺件)
      grep -w "缺件" ngType.txt | awk '{print $1,$2}'
      ;;
    脚翘)
      grep -w "脚翘" ngType.txt | awk '{print $1,$2}'
      ;;
    立碑)
      grep -w "立碑" ngType.txt | awk '{print $1,$2}'
      ;;
    翻件)
      grep -w "翻件" ngType.txt | awk '{print $1,$2}'
      ;;
    虚焊)
      grep -w "虚焊" ngType.txt | awk '{print $1,$2}'
      ;;
    返回)
      break
      ;;
    esac
    echo
  done
}

while true
do 
  clear
  echo "Please choice Data Type:"
  echo "  1.OKtype Data"
  echo "  2.ngType Data"
  echo "  3.Exit";read num
  
  if [ $num == "1" ] 
  then
    okTypePrint
  elif [ $num == "2" ]
  then  
    ngTypePrint
  elif [ $num == "3" ]
  then
    break
  fi
done    




























