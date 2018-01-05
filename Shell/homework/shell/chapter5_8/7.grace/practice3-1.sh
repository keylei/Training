#! /bin/bash
#=====================================================================================================================================================
#1.1 当前目录下创建LINE1, LINE2两个目录, 然后按照当前系统时间每隔5s创建文件, 文件名的格式根据当前的系统时间决定
#1.2 文件内容第一行为title, 一共有5列, 分别为ID, Height,Name, Result,NgType和Time, 每个文件有至少20条记录(具体多少条根据位置参数决定),每个字段以制表符隔开, 文件内容的具体格式如下:
#=====================================================================================================================================================
#判断目录LINE1，LINE2是否存在不存在则创建
[ ! -d ./LINE1 ] && mkdir LINE1 
[ ! -d ./LINE2 ] && mkdir LINE2

#判断第一个参数是否存在以及是否符合要求
let MIN=20;                                                        #参数最大值设置为30最小值设置为20
let MAX=30;
count=$1                                                           #第一个参数赋值给count
[ ! $1 ] && { echo "请输入一个参数，形如：$0 $MIN";exit 1;}
[ "$(echo $1 | bc 2>/dev/null)" != "$1" ] && { echo "请输入数字参数，形如：$0 $MIN";exit 1;}
[ "$(echo $1 | grep "\." >/dev/null)" != "" ] && { echo "请输入整形参数，形如：$0 $MIN";exit 1;}
[ $1 -lt $MIN ] && { echo "参数过小（$MIN ~ $MAX），形如：$0 $MIN";exit 1;}	
[ $1 -gt $MAX ] && { echo "参数过大（$MIN ~ $MAX），形如：$0 $MAX";exit 1;}

#定义数组Result,Name,NgType供下面选择时按位置随机选择
declare -a Result=('OK' 'NG')
declare -a Name=('R1' 'R2' 'C1' 'C2' 'IC1' 'IC2' 'Bga1' 'Bga2')
declare -a NgType=('错料' '偏移' '异物' '桥联' '多锡' '缺件' '脚翘' '立碑' '翻件' '虚焊')

#生成随机数
definition()
{
        Time=`date +"%F %T"`
        let NUM1=$RANDOM%8                                         #随机调用Name数组位置（0-7）
        let NUM3=$RANDOM%2                                         #随机调用Result数组位置（0-1）
        let NUM4=$RANDOM%10                                        #随机调用NgType数组位置（0-9）
        let heighti=$RANDOM%300+300                                #生成300到600之间的随机数（整数）
        let heightp=$RANDOM%100
        NUM2=$(echo "scale=2;$heighti+0.01*$heightp" | bc)         #生成300到600之间的随机数（浮点）
}

#创建以时间作为文件名文件的文件输入表头
create()
{
filename=$(date +%y%m%d%H%M%S).txt
echo -en "ID\t\tName\t\tHight\t\tResult\t\tNgType\t\tTime\t\n"  > ./LINE1/$filename
echo -en "ID\t\tName\t\tHight\t\tResult\t\tNgType\t\tTime\t\n"  > ./LINE2/$filename

#在文件中输入随机数
for (( i=1;i<=count;i++ ))
do
        definition                                                  #调用definition函数
        echo -en "$i\t\t${Name[$NUM1]}\t\t$NUM2\t\t${Result[$NUM3]}\t\t${NgType[$NUM4]}\t\t$Time\n" >> ./LINE1/$filename
        definition
        echo -en "$i\t\t${Name[$NUM1]}\t\t$NUM2\t\t${Result[$NUM3]}\t\t${NgType[$NUM4]}\t\t$Time\n" >> ./LINE2/$filename
done
}

#每5秒创建文件
circle()
{
while true
do
        create                                                     #调用create函数                                                     
        sleep 5
        
done
}

PS3="MAKE YOUR CHOICE:"                                            #设置环境参数PS3（即终端显示）
select choice in circle Exit
do
        case $choice in
            circle)
                echo "每5秒创建文件"
                echo "按CTRL+C结束创建文件"
                circle
                ;;
            Exit)
                break
                ;;
            *)
                echo "输入错误！"
                exit
                ;;
        esac
done

exit 0


