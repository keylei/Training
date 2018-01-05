#!/bin/bash

# define Running condition
declare -r MINDATA_COUNTS=20
declare -r MAXDATA_COUNTS=50

# Argument judge
[ $# == 0 ] && { echo "请传入创建参数(创建数据数量)，形如：$0 $MINDATA_COUNTS";exit 1;}

# judge if the $1 is an num
[ "$(echo $1 | bc 2>/dev/null)" != "$1" ] && { echo "请输入数字参数，形如：$0 $MINDATA_COUNTS";exit 1;}

[ "$(echo $1 | grep "\." >/dev/null)" != "" ] && { echo "请输入整形参数，形如：$0 $MINDATA_COUNTS";exit 1;}

[ $1 -lt $MINDATA_COUNTS ] && { echo "参数过小（$MINDATA_COUNTS ～ $MAXDATA_COUNTS），形如：$0 $MINDATA_COUNTS";exit 1;}
	
[ $1 -gt $MAXDATA_COUNTS ] && { echo "参数过大（$MINDATA_COUNTS ～ $MAXDATA_COUNTS），形如：$0 $MINDATA_COUNTS";exit 1;}


# Accept the parameters and define data create condition
datacount=$1


declare -a PARTNAME_ARRAY=('R1' 'R2' 'C1' 'C2' 'IC1' 'IC2' 'BGA1' 'BGA2')
declare -r PARTNAME_COUNT=8
declare -a NGTYPE_ARRAY=('错料' '偏移' '异物' '桥联' '多锡' '缺件' '脚翘' '立碑' '翻件' '虚焊' 'N/A')
declare -r NGTYPE_COUNT=10
declare -a RESUALT_STA=('OK' 'NG')
declare -r RESUALT_COUNT=2

RANDOM=$(date +%s)  # Give the random a uniq seed

# Get random data to wrinte every create file
getrandomdata()
{
		# random partname & resualt & ngtype
		let index_p=$RANDOM%$PARTNAME_COUNT
    let index_r=$RANDOM%$RESUALT_COUNT
		let index_n=$RANDOM%$NGTYPE_COUNT
		[ $index_r == 0 ] && { index_n=10; } #if resualt is ok then ngtype is 'N/A'
		# random height
		let heighti=$RANDOM%300+300
    let heightp=$RANDOM%100
    heightf=$(echo "scale=2;$heighti+0.01*$heightp" | bc)
}

# Creat files function
createfiles()
{
  # make line1 and lin2 directory
  [ ! -d "./Line1" ] && { mkdir Line1; }
  [ ! -d "./Line2" ] && { mkdir Line2; }

  filename="$(date +"%Y%m%d%H%M%S").txt"
  # title
	printf "%-5s%-6s%-10s%-10s%-15s\t\t\t%-15s \n" "ID"	"Name" "Height"  "Result"	"NgType" "Time" > "./Line1/${filename}"
  printf "%-5s%-6s%-10s%-10s%-15s\t\t\t%-15s \n" "ID"	"Name" "Height"  "Result"	"NgType" "Time" > "./Line2/${filename}"
  # data
	for (( i=1; i<datacount+1; i++ ))
	do
		getrandomdata
		printf "%-5s%-6s%-10.2f%-10s%-15s\t\t\t%-15s \n" ${i} ${PARTNAME_ARRAY[$index_p]} $heightf \
		${RESUALT_STA[$index_r]} ${NGTYPE_ARRAY[$index_n]} "$(date +"%F %T")" >>"./Line1/$filename"
		getrandomdata
		printf "%-5s%-6s%-10.2f%-10s%-15s\t\t\t%-15s \n" ${i} ${PARTNAME_ARRAY[$index_p]} $heightf \
		${RESUALT_STA[$index_r]} ${NGTYPE_ARRAY[$index_n]} "$(date +"%F %T")" >>"./Line2/$filename"
	done
}

# Define 5 second tick time function
ticktimecreatfile()
{
	while true
	do
		createfiles
		sleep 5
	done
  exit 0
}

ticktimecreatfile &

FILECREATEPROGRESS_PID=$!

# control the data create progress
PS3="Please select what you want:"
select chn in "Exit" "Pause" "Resume"
do
	case $chn in
		Exit)
			echo "exit"
			kill $FILECREATEPROGRESS_PID >/dev/null 2>&1
   		exit 0
		;;
		Pause)
			kill -STOP $FILECREATEPROGRESS_PID
		;;
		Resume)
			kill -CONT $FILECREATEPROGRESS_PID
		;;
		*)
			echo "Wrong choice!"
		;;
	esac
done

exit 0

