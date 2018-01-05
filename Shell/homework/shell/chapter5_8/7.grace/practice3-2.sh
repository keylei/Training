#! /bin/bash
#===============================================================================================================
#2.1 在当前目录下生成一张cad.txt文档
#把LINE1和LINE2的所有文件名(不包含扩展名)输出到cad.txt文件中, 每行一个
#根据LINE1和LINE2中所有的数据生成一张表输出到cad.txt, 生成如下的表
#使用case, 通过选择元件的Name来输出相应的OK(%)
#2.2 在当前目录下生成一张ngType.txt文档
#把LINE1和LINE2的所有文件名(不包含扩展名)输出到ngType.txt文件中, 每行一个
#根据LINE1和LINE2中所有的数据生成一张表, 统计在NG的元件中各个NgType所占的比例,输出到ngtype.txt
#支持使用select, 通过选择NgType来输出相应的OK(%)
#===============================================================================================================
cl_ng=`cat ./LINE*/* | grep NG |wc -l`          #统计文件中ng的行数
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
echo "LINE1 LINE2:" > cad.txt                                                                    #创建cad.txt文件并输入LINE1 LINE2：
                                                                   
while read i                                                                                      
do
    FILE=("${FILE[@]}" "$i")
done < <(find "./LINE1/" "./LINE2" -name "*.txt" -type f)                                        #把文件名存到FILE数组中
for var in ${FILE[@]} 
do
    echo ${var%.*} >> cad.txt                  #去文件后缀名并输入到文件中
    echo ${var%.*} > ngType.txt                #创建ngType.txt函数并输入去后缀的文件名
done

echo -en "Name\t\tOK(%)\t\t\tHEIGHT(MAX)\t\tHEIGHT(MIN)\t\tHEIGHT(Avg)\t\t\n"  >> cad.txt
echo -en "NgType\t\tNg\t\t\n"  > ngType.txt

for Filename in "${FILE[@]}"
do 
    while read ID Name Hight Result NgType Time	                                                 #逐行读取文件内容
    do
        case $Name in
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

#读取数据
for (( j=0;j<8;j++ ))                                               
do
    OK_PER[j]=$(echo "scale=4;${OK_count[j]}/${ALL_count[j]}*100" |bc)
    HEIGTH_Avg[j]=$(echo "scale=2;${SUM[j]}/${ALL_count[j]}" |bc)
    printf "%-11s %-11.2f %-15.2f %-15.2f %-10.2f\n" ${Name_1[j]} ${OK_PER[j]} \
${HEIGTH_MAX[j]} ${HEIGTH_MIN[j]} ${HEIGTH_Avg[j]} >> cad.txt    
done

#查询LINE1，LINE2目录下Result为NG的ngType各个类型所占百分比
cl_PER=$(echo "scale=4;`cat ./LINE*/* | grep NG | grep 错料 |wc -l`/$cl_ng*100" |bc )
py_PER=$(echo "scale=4;`cat ./LINE*/* | grep NG | grep 偏移 |wc -l`/$cl_ng*100" |bc )
yw_PER=$(echo "scale=4;`cat ./LINE*/* | grep NG | grep 异物 |wc -l`/$cl_ng*100" |bc )
ql_PER=$(echo "scale=4;`cat ./LINE*/* | grep NG | grep 桥联 |wc -l`/$cl_ng*100" |bc )
dx_PER=$(echo "scale=4;`cat ./LINE*/* | grep NG | grep 多锡 |wc -l`/$cl_ng*100" |bc )
qj_PER=$(echo "scale=4;`cat ./LINE*/* | grep NG | grep 缺件 |wc -l`/$cl_ng*100" |bc )
jq_PER=$(echo "scale=4;`cat ./LINE*/* | grep NG | grep 脚翘 |wc -l`/$cl_ng*100" |bc )
lb_PER=$(echo "scale=4;`cat ./LINE*/* | grep NG | grep 立碑 |wc -l`/$cl_ng*100" |bc )
fj_PER=$(echo "scale=4;`cat ./LINE*/* | grep NG | grep 翻件 |wc -l`/$cl_ng*100" |bc )
xh_PER=$(echo "scale=4;`cat ./LINE*/* | grep NG | grep 虚焊 |wc -l`/$cl_ng*100" |bc )
printf "错料\t\t\t%-8.2f\n偏移\t\t\t%-8.2f\n异物\t\t\t%-8.2f\n桥联\t\t\t%-8.2f\n多锡\t\t\t%-8.2f\n" \
$cl_PER $py_PER $yw_PER $ql_PER $dx_PER >> ngType.txt
 
while true	                                #case语句实现输入Name输出相应OK（%）可以循环输入
do
echo -en "Please input: R1/R2/C1/C2/IC1/IC2/Bga1/Bga2\n"
echo "Input others will exit !"
read input
        echo -en "NgType\t Ng(%)\n"        
        case $input in
            R1 )
            printf "%-9s%-4.2f\n" R1 ${OK_PER[0]} 
            ;;
            R2 )
            printf "%-9s%-4.2f\n" R2 ${OK_PER[1]} 
            ;;
            C1)      
            printf "%-9s%-4.2f\n" C1 ${OK_PER[2]}  
            ;;
            C2) 
            printf "%-9s%-4.2f\n" C2 ${OK_PER[3]}  
            ;;
            IC1)
            printf "%-9s%-4.2f\n" IC1 ${OK_PER[4]} 
            ;;
            IC2)
            printf "%-9s%-4.2f\n" IC2 ${OK_PER[5]}  
            ;;
            Bga1)
            printf "%-9s%-4.2f\n" Bga1 ${OK_PER[6]} 
            ;;
            Bga2)
            printf "%-9s%-4.2f\n" Bga2 ${OK_PER[7]}  
            ;;
            *)
            echo "input wrong!"
            break;
            ;;
        esac          
done 


PS3="MAKE YOUR CHOICE:"                                                                          #设置PS3环境变量即在终端显示的内容
select choice in 错料 偏移 异物 桥联 多锡 缺件 脚翘 立碑 翻件 虚焊                                     #通过select语句进行ngType选择输出相应百分比
do
    case $choice in
        错料)
        echo -en "NgType\tNg(%)\n"
        printf "错料\t%4.2f\n " $cl_PER
        ;;
        偏移)
        echo -en "NgType\tNg(%)\n\n"
        printf "偏移\t%4.2f\n" $py_PER
        ;;
        异物) 
        echo -en "NgType\tNg(%)\n\n"     
        printf "异物\t%4.2f\n" $yw_PER 
        ;;
        桥联)
        echo -en "NgType\tNg(%)\n\n"
        printf "桥联\t%4.2f\n" $ql_PER 
        ;;
        多锡)
        echo -en "NgType\tNg(%)\n\n" 
        printf "多锡\t%4.2f\n" $dx_PER 
        ;;
        缺件)
        echo -en "NgType\tNg(%)\n\n"
        printf "缺件\t%4.2f\n" $qj_PER 
        ;;
        脚翘)
        echo -en "NgType\tNg(%)\n\n"
        printf "脚翘\t%4.2f\n" $jq_PER 
        ;;
        立碑)
        echo -en "NgType\tNg(%)\n\n"
        printf "立碑\t%4.2f\n" $lb_PER 
        ;;
        翻件)
        echo -en "NgType\tNg(%)\n\n"
        printf "翻件\t%4.2f\n" $fj_PER 
        ;;
        虚焊)
        echo -en "NgType\tNg(%)\n\n"
        printf "虚焊\t%4.2f\n" $xh_PER 
        ;;
        
        *)
        exit 0
        ;;
    esac

done

exit 0

