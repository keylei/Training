#!/bin/bash

# define Running condition
CADFILENAME="cad.txt"
NGTYPEFILENAME="ngType.txt"

# Accept the parameters and define data create condition
declare -a PARTNAME_ARRAY=('R1' 'R2' 'C1' 'C2' 'IC1' 'IC2' 'BGA1' 'BGA2')
declare -r PARTNAME_COUNT=8
declare -a NGTYPE_ARRAY=('错料' '偏移' '异物' '桥联' '多锡' '缺件' '脚翘' '立碑' '翻件' '虚焊')
declare -r NGTYPE_COUNT=10
declare -a RESUALT_STA=('OK' 'NG')
declare -r RESUALT_COUNT=2
declare -a FileNames                                                   #save the line1 and line2 file names
declare -ia okcnt=(0 0 0 0 0 0 0 0)                                    #save part ok count. okcnt[0]...okcnt[7] to R1...BGA2
declare -ia partcnt=(0 0 0 0 0 0 0 0)                                  #save part count. partcnt[0]...partcnt[7] to R1...BGA2
declare -ia ngtypecnt=(0 0 0 0 0 0 0 0 0 0)                            #save ngtype count. ngtypecnt[0]...ngtypecnt[9] to 错料...虚焊
declare -a maxheight=('0' '0' '0' '0' '0' '0' '0' '0')                 #save maxheight. maxheight[0]...maxheight[7] to R1...BGA2
declare -a minheight=('600' '600' '600' '600' '600' '600' '600' '600') #save minheight. minheight[0]...minheight[7] to R1...BGA2
declare -a avgheight=('0' '0' '0' '0' '0' '0' '0' '0')                 #save avgheight. avgheight[0]...avgheight[7] to R1...BGA2
declare -a tempheightsum=('0' '0' '0' '0' '0' '0' '0' '0')             #temp save height sum. tempheightsum[0]...tempheightsum [7] to R1...BGA2


###############################functions###############################

# Find all files in directory line1 and line2
findFileNamesToCad()
{
	# check line1 and lin2 directory if dont have dir then exit 1
  [ -d "./Line1" ] || { [ ! -d "./Line2" ] && { exit 1; echo "there do not have Line1 or Line2 dir"; }; }

	# check in line1 and lin2 directory if dont have file then exit 1
	[ `ls Line{1,2} | wc -w` == 0 ] && { exit 1; echo "there do not have file in Line1 and Line2 dir"; }

	echo "All data files:" > $CADFILENAME
	while read line
	do 
		FileNames[$indexCounter]=$line
		let indexCounter+=1
		echo ${line%.*} >> $CADFILENAME          # remove the file extension name and write to cad.txt file
	done < <(find "./Line1" "./Line2" -type f)
}

# Update statistics resualt and save to files function
updateStatisticsFile()
{
  # title
	printf "\n%-6s%-8s%-15s%-15s%-15s\n" "Name"	"OK(%)" "HEIGTH(MAX)" "HEIGTH(MIN)" "HEIGTH(Avg)" >> ${CADFILENAME}
	printf "%-10s%-20s\n" "NgType" "NG(%)" > ${NGTYPEFILENAME}

  # data statistics
	for filename in ${FileNames[@]}
	do
		while read ID	Name Height  Result	NgType Time
		do
			[ $ID == ID ] && { continue; }
			#########################################cad file data statistics
			case $Name in
				"${PARTNAME_ARRAY[0]}")   
					 let partcnt[0]+=1
					 [ $Result == ${RESUALT_STA[0]} ] && { let okcnt[0]+=1; }
					 [ $(echo "$Height > ${maxheight[0]}" | bc) == 1 ] && { maxheight[0]=$Height; }   
					 [ $(echo "$Height < ${minheight[0]}" | bc) == 1 ] && { minheight[0]=$Height; }
					 tempheightsum[0]=$(echo "$Height + ${tempheightsum[0]}" | bc)
				;;
				"${PARTNAME_ARRAY[1]}")
					 let partcnt[1]+=1
					 [ $Result == ${RESUALT_STA[0]} ] && { let okcnt[1]+=1; }
					 [ $(echo "$Height > ${maxheight[1]}" | bc) == 1 ] && { maxheight[1]=$Height; }   
					 [ $(echo "$Height < ${minheight[1]}" | bc) == 1 ] && { minheight[1]=$Height; }
					 tempheightsum[1]=$(echo "$Height + ${tempheightsum[1]}" | bc)
				;;
				"${PARTNAME_ARRAY[2]}")
					 let partcnt[2]+=1
					 [ $Result == ${RESUALT_STA[0]} ] && { let okcnt[2]+=1; }
					 [ $(echo "$Height > ${maxheight[2]}" | bc) == 1 ] && { maxheight[2]=$Height; }   
					 [ $(echo "$Height < ${minheight[2]}" | bc) == 1 ] && { minheight[2]=$Height; }
					 tempheightsum[2]=$(echo "$Height + ${tempheightsum[2]}" | bc)
				;;
				"${PARTNAME_ARRAY[3]}")
					 let partcnt[3]+=1
					 [ $Result == ${RESUALT_STA[0]} ] && { let okcnt[3]+=1; }
					 [ $(echo "$Height > ${maxheight[3]}" | bc) == 1 ] && { maxheight[3]=$Height; }   
					 [ $(echo "$Height < ${minheight[3]}" | bc) == 1 ] && { minheight[3]=$Height; }
					 tempheightsum[3]=$(echo "$Height + ${tempheightsum[3]}" | bc)
				;;
				"${PARTNAME_ARRAY[4]}")
					 let partcnt[4]+=1
					 [ $Result == ${RESUALT_STA[0]} ] && { let okcnt[4]+=1; }
					 [ $(echo "$Height > ${maxheight[4]}" | bc) == 1 ] && { maxheight[4]=$Height; }   
					 [ $(echo "$Height < ${minheight[4]}" | bc) == 1 ] && { minheight[4]=$Height; }
					 tempheightsum[4]=$(echo "$Height + ${tempheightsum[4]}" | bc)
				;;
				"${PARTNAME_ARRAY[5]}")
					 let partcnt[5]+=1
					 [ $Result == ${RESUALT_STA[0]} ] && { let okcnt[5]+=1; }
					 [ $(echo "$Height > ${maxheight[5]}" | bc) == 1 ] && { maxheight[5]=$Height; }   
					 [ $(echo "$Height < ${minheight[5]}" | bc) == 1 ] && { minheight[5]=$Height; }
					 tempheightsum[5]=$(echo "$Height + ${tempheightsum[5]}" | bc)
				;;
				"${PARTNAME_ARRAY[6]}")
					 let partcnt[6]+=1
					 [ $Result == ${RESUALT_STA[0]} ] && { let okcnt[6]+=1; }
					 [ $(echo "$Height > ${maxheight[6]}" | bc) == 1 ] && { maxheight[6]=$Height; }   
					 [ $(echo "$Height < ${minheight[6]}" | bc) == 1 ] && { minheight[6]=$Height; }
					 tempheightsum[6]=$(echo "$Height + ${tempheightsum[6]}" | bc)
				;;
				"${PARTNAME_ARRAY[7]}")
					 let partcnt[7]+=1
					 [ $Result == ${RESUALT_STA[0]} ] && { let okcnt[7]+=1; }
					 [ $(echo "$Height > ${maxheight[7]}" | bc) == 1 ] && { maxheight[7]=$Height; }   
					 [ $(echo "$Height < ${minheight[7]}" | bc) == 1 ] && { minheight[7]=$Height; }
					 tempheightsum[7]=$(echo "$Height + ${tempheightsum[7]}" | bc)
				;;
				*)
					
				;;
			esac

			#########################################ngType file data statistics
			case $NgType in   
				"${NGTYPE_ARRAY[0]}")   
					 let ngtypecnt[0]+=1
				;;
				"${NGTYPE_ARRAY[1]}")
					 let ngtypecnt[1]+=1
				;;
				"${NGTYPE_ARRAY[2]}")
					 let ngtypecnt[2]+=1
				;;
				"${NGTYPE_ARRAY[3]}")
					 let ngtypecnt[3]+=1
				;;
				"${NGTYPE_ARRAY[4]}")
					 let ngtypecnt[4]+=1
				;;
				"${NGTYPE_ARRAY[5]}")
					 let ngtypecnt[5]+=1
				;;
				"${NGTYPE_ARRAY[6]}")
					 let ngtypecnt[6]+=1
				;;
				"${NGTYPE_ARRAY[7]}")
					 let ngtypecnt[7]+=1
				;;
				"${NGTYPE_ARRAY[8]}")
					 let ngtypecnt[8]+=1
				;;
				"${NGTYPE_ARRAY[9]}")
					 let ngtypecnt[9]+=1
				;;
				*)
					
				;;
			esac

		done <$filename
	done

	# statistics resualt ok data and write to cad.txt
	for (( i=0; i<PARTNAME_COUNT; i++ ))
	do
		avgheight[$i]=$(echo "scale=2;${tempheightsum[$i]} / ${partcnt[$i]}" | bc)
    okpercent=$(echo "scale=4; ${okcnt[$i]} / ${partcnt[$i]} * 100" | bc)
		printf "%-6s%-8.2f%-15.2f%-15.2f%-15.2f\n" ${PARTNAME_ARRAY[$i]} $okpercent ${maxheight[$i]} ${minheight[$i]} ${avgheight[$i]} >>$CADFILENAME
	done

	# statistics ngType data and write to cad.txt

  for (( j=0; j<NGTYPE_COUNT; j++ ))  
	do
			let ngCntSum+=ngtypecnt[$j]   # the ng sum cnt
	done

	for (( i=0; i<NGTYPE_COUNT; i++ ))
	do
    ngpercent=$(echo "scale=4; ${ngtypecnt[$i]} / $ngCntSum * 100" | bc)
		printf "%-10s   %-20.2f\n" ${NGTYPE_ARRAY[$i]} $ngpercent >>$NGTYPEFILENAME
	done
}

#########################run Statistics and file create functions#######################

findFileNamesToCad

updateStatisticsFile


#########################show part of cad.txt and ngType file###########################

# use the case

read -p	"Please input the part number to show the statistics info:"  partname

partname=$(echo $partname | tr a-z A-Z)

case $partname in
				"${PARTNAME_ARRAY[0]}" | "${PARTNAME_ARRAY[1]}" | "${PARTNAME_ARRAY[3]} " | "${PARTNAME_ARRAY[4]}" \
					| "${PARTNAME_ARRAY[5]}" | "${PARTNAME_ARRAY[6]}" | "${PARTNAME_ARRAY[7]}")
					 data="$(cat $CADFILENAME | grep "Name")"
				   echo -e "${data:0:12}"
					 data=$(cat $CADFILENAME | grep -i $partname)
					 echo -e "${data:0:12}\n"
				;;
				*)
					 echo -e "\nskip show cad.txt info\n"
				;;
esac


# use the select

echo -e "ngType percentage check:"

PS3="Please select what you want:"

a=( "${NGTYPE_ARRAY[@]}" "Exit" )

select chn in "${a[@]}"
do
		if [ "$chn" != "" ]
		then
			[ $chn == "Exit" ] && { exit 0; }
			echo -e "$(cat $NGTYPEFILENAME | grep "NgType")"
			echo -e "$(cat $NGTYPEFILENAME | grep -i $chn)\n"
		fi
done

exit 0

