#============================================================================================================================================
#3. 创建一个脚本, 统计最近生产信息
#脚本接受一个参数, 参数往前进行统计的时间数. 如输入5, 就是往前推5s, 10就是10s
#根据输入的时间生成统计时间范围到search.txt文档
#根据时间统计表1中TIME满足要求的所有元件, 这张表生成类似与表1, 到search.txt
#============================================================================================================================================
#! /bin/bash
[ ! $1 ] && { echo "请输入一个参数，形如：$0 5";exit 1;}                                           #判断输入参数的是否符合要求
[ "$(echo $1 | bc 2>/dev/null)" != "$1" ] && { echo "请输入数字参数，形如：$0 5";exit 1;}
[ "$(echo $1 | grep "\." >/dev/null)" != "" ] && { echo "请输入整形参数，形如：$0 5";exit 1;}

let time1=`date +%s`                                                                           #把当前时间转换成时间戳
let time=time1-$1                                                                              #减去输入的参数，求时间范围  
                                                                           
echo $(date -d "1970-01-01 UTC $time seconds" "+%F %T")-$(date -d "1970-01-01 UTC $time1 seconds" "+%F %T") > ./search.txt
echo -en "ID\t\tName\t\tHight\t\tResult\t\tNgType\t\tTime\t\n"  >> ./search.txt  
              
while read i                                                                                   #把文件名存到数组中                                             
do
    FILE=("${FILE[@]}" "$i")
done < <(find "./LINE1/" "./LINE2" -name "*.txt" -type f) 

for var in ${FILE[@]} 
do
    echo ${var%.*}
done

for Filename in "${FILE[@]}"
do 
    while read ID Name Hight Result NgType Time	                                               #遍历文件找出符合时间要求的文件并输出相应数据
    do
        [ $ID == ID ] && { continue; }
        let DA=$(date +%s -d "${Time}") 
        [ $DA -ge $time ] && [ $DA -le $time1 ] && { echo -en "$ID\t\t$Name\t\t$Hight\t\t$Result\t\t$NgType\t\t$Time\t\n"  >> ./search.txt;}
    done <$Filename

done

exit 0
