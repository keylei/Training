#===========================================================================================================================
#4.创建一个间隔为一分钟的后台定时任务
#总是统计所有元件的OK/NG情况, 当有任何一个元件的OK%低于30%时, 生成一张类似与2的表格到realtime.txt(只有一条记录, 即第一次触发该条件的元件)
#把realtime.txt前两个例输出的屏幕
#把LINE1和LINE2所有数据按照其目录结构进行bzip2压缩备份
#===========================================================================================================================
#! /bin/bash
#. practice3-1.sh
null=$(echo "scale=2;0" |bc)                    #null定义为浮点数0为下面数组定义和比较max做准备
Null=$(echo "scale=2;600.00" |bc)               #Null定义为浮点数600.00为下面比较min做准备
declare -ai OK_count=(0 0 0 0 0 0 0 0)          #定义数组统计R1到Bga2的Result为OK的数量
declare -ai ALL_count=(0 0 0 0 0 0 0 0)         #定义数组统计R1到Bga2的数量
declare -a Name_1=('R1' 'R2' 'C1' 'C2' 'IC1' 'IC2' 'Bga1' 'Bga2')                        
declare -a NgType=('错料' '偏移' '异物' '桥联' '多锡' '缺件' '脚翘' '立碑' '翻件' '虚焊')
declare -a OK_PER=($null $null $null $null $null $null $null $null)                              #定义数组统计R1到Bga2的OK（%）
declare -a SUM=($null $null $null $null $null $null $null $null)                                 #定义数组统计R1到Bga2的Hight的总值求Hight的平均值
declare -a HEIGTH_MAX=($null $null $null $null $null $null $null $null)                          #定义数组统计R1到Bga2的Hight最大值
declare -a HEIGTH_MIN=($Null $Null $Null $Null $Null $Null $Null $Null)                          #定义数组统计R1到Bga2的Hight最小值
declare -a HEIGTH_Avg=($null $null $null $null $null $null $null $null)                          #定义数组统计R1到Bga2的Hight平均值
declare -a Ng_PER=($null $null $null $null $null $null $null $null $null $null)                  #定义数组统计R1到Bga2所有在Ng的元件中各个NgType占有的比例

while read i 
do
    FILE=("${FILE[@]}" "$i")
done < <(find "./LINE1/" "./LINE2" -name "*.txt" -type f)                                        #把文件名存到FILE数组中

for Filename in "${FILE[@]}"
do 

    while read ID Name Hight Result NgType Time	
    do
        case $Name in                                                                            #通过case语句实现对每个Name的Hight情况进行统计
            R1)
                let ALL_count[0]++ 
                [ "${Result}" == "OK" ] && { let OK_count[0]++; }
                [ $(echo "$Hight >= ${HEIGTH_MAX[0]}"|bc) = 1 ] && HEIGTH_MAX[0]=$Hight
                [ $(echo "$Hight <= ${HEIGTH_MIN[0]}"|bc) = 1 ] && HEIGTH_MIN[0]=$Hight           
                SUM[0]=$(echo "${SUM[0]}+$Hight" |bc)                     
            ;;

            R2)
                let ALL_count[1]++ 
                [ "${Result}" == "OK" ] && { let OK_count[1]++; }
                [ $(echo "$Hight >= ${HEIGTH_MAX[1]}"|bc) = 1 ] && HEIGTH_MAX[1]=$Hight
                [ $(echo "$Hight <= ${HEIGTH_MIN[1]}"|bc) = 1 ] && HEIGTH_MIN[1]=$Hight           
                SUM[1]=$(echo "${SUM[1]}+$Hight" |bc)                     
            ;;

            C1)
                let ALL_count[2]++ 
                [ "${Result}" == "OK" ] && let OK_count[2]++
                [ $(echo "$Hight >= ${HEIGTH_MAX[2]}"|bc) = 1 ] && HEIGTH_MAX[2]=$Hight
                [ $(echo "$Hight <= ${HEIGTH_MIN[2]}"|bc) = 1 ] && HEIGTH_MIN[2]=$Hight           
                SUM[2]=$(echo "${SUM[2]}+$Hight" |bc)                     
            ;;

            C2)
                let ALL_count[3]++ 
                [ "${Result}" == "OK" ] && let OK_count[3]++
                [ $(echo "$Hight >= ${HEIGTH_MAX[3]}"|bc) = 1 ] && HEIGTH_MAX[3]=$Hight
                [ $(echo "$Hight <= ${HEIGTH_MIN[3]}"|bc) = 1 ] && HEIGTH_MIN[3]=$Hight           
                SUM[3]=$(echo "${SUM[3]}+$Hight" |bc)                     
            ;;

            IC1)
                let ALL_count[4]++ 
                [ "${Result}" == "OK" ] && let OK_count[4]++
                [ $(echo "$Hight >= ${HEIGTH_MAX[4]}"|bc) = 1 ] && HEIGTH_MAX[4]=$Hight
                [ $(echo "$Hight <= ${HEIGTH_MIN[4]}"|bc) = 1 ] && HEIGTH_MIN[4]=$Hight           
                SUM[4]=$(echo "${SUM[4]}+$Hight" |bc)                     
            ;;
            IC2)
                let ALL_count[5]++ 
                [ "${Result}" == "OK" ] && let OK_count[5]++
                [ $(echo "$Hight >= ${HEIGTH_MAX[5]}"|bc) = 1 ] && HEIGTH_MAX[5]=$Hight
                [ $(echo "$Hight <= ${HEIGTH_MIN[5]}"|bc) = 1 ] && HEIGTH_MIN[5]=$Hight           
                SUM[5]=$(echo "${SUM[5]}+$Hight" |bc)                    
            ;;

            Bga1)
                let ALL_count[6]++ 
                [ "${Result}" == "OK" ] && let OK_count[6]++
                [ $(echo "$Hight >= ${HEIGTH_MAX[6]}"|bc) = 1 ] && HEIGTH_MAX[6]=$Hight
                [ $(echo "$Hight <= ${HEIGTH_MIN[6]}"|bc) = 1 ] && HEIGTH_MIN[6]=$Hight           
                SUM[6]=$(echo "${SUM[6]}+$Hight" |bc)                     
            ;;

            Bga2)
                let ALL_count[7]++ 
                [ "${Result}" == "OK" ] && let OK_count[7]++
                [ $(echo "$Hight >= ${HEIGTH_MAX[7]}"|bc) = 1 ] && HEIGTH_MAX[7]=$Hight
                [ $(echo "$Hight <= ${HEIGTH_MIN[7]}"|bc) = 1 ] && HEIGTH_MIN[7]=$Hight           
                SUM[7]=$(echo "${SUM[7]}+$Hight" |bc)                     
            ;;

            *)
            ;;
        esac          
    done <$Filename

done

echo -en "Name\t\tOK(%)\t\tHEIGHT(MAX)\t\tHEIGHT(MIN)\t\tHEIGHT(Avg)\t\t\n"  > realtime.txt      #创建realtime.txt并输入表头
                                                                                                 #通过for循环实现对数据的输出
for (( j=0;j<8;j++ ))                                                                          
do 
    HEIGTH_Avg[j]=$(echo "scale=2;${SUM[j]}/${ALL_count[j]}" |bc)
    OK_PER[j]=$(echo "scale=4;${OK_count[j]}/${ALL_count[j]}*100" |bc)
    [ $(echo "${OK_PER[$j]} < 50"|bc) = 1 ] && { printf "%-11s %-11.2f %-15.2f %-15.2f %-10.2f\n" \
${Name_1[j]} ${OK_PER[j]} ${HEIGTH_MAX[j]} ${HEIGTH_MIN[j]} ${HEIGTH_Avg[j]} >> realtime.txt; } && { break; }   
done

filename=$(date +%y%m%d%H%M%S)                                                                   #压缩包以时间戳形式命名
awk '{print $1,$2}' realtime.txt >> realtime.txt                                                 #打印出第一二列
tar -cjvf ${filename}.tar.bz2 ./LINE*/*.txt                                                      #对LINE1,LINE2目录进行打包压缩 
                                                           
exit 0

