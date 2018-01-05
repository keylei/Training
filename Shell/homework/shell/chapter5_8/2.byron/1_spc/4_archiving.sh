#!/bin/bash


# define Running condition
WARNING_THRESHOLD=50              # when less this THRESHOLD will warn
REALTIMEFILENAME="realtime.txt"
COMPFILEDIRETOR=Line

# file out put path
shell_path="$(cd `dirname $0`; pwd)"

# define runing var
declare -a PARTNAME_ARRAY=('R1' 'R2' 'C1' 'C2' 'IC1' 'IC2' 'BGA1' 'BGA2')
declare -r PARTNAME_COUNT=8
declare -a RESUALT_STA=('OK' 'NG')
declare -r RESUALT_COUNT=2
declare -a FileNames                                                   #save the line1 and line2 file names
declare -ia okcnt=(0 0 0 0 0 0 0 0)                                    #save part ok count. okcnt[0]...okcnt[7] to R1...BGA2
declare -ia partcnt=(0 0 0 0 0 0 0 0)                                  #save part count. partcnt[0]...partcnt[7] to R1...BGA2
declare -a maxheight=('0' '0' '0' '0' '0' '0' '0' '0')                 #save maxheight. maxheight[0]...maxheight[7] to R1...BGA2
declare -a minheight=('600' '600' '600' '600' '600' '600' '600' '600') #save minheight. minheight[0]...minheight[7] to R1...BGA2
declare -a avgheight=('0' '0' '0' '0' '0' '0' '0' '0')                 #save avgheight. avgheight[0]...avgheight[7] to R1...BGA2
declare -a tempheightsum=('0' '0' '0' '0' '0' '0' '0' '0')             #temp save height sum. tempheightsum[0]...tempheightsum [7] to R1...BGA2

###############################functions###############################

# Find all files in directory line1 and line2
findFileNames()
{
	while read line
	do 
		FileNames[$indexCounter]=$line
		let indexCounter+=1
	done < <(find "./Line1" "./Line2" -type f)
}

# Update statistics resualt and save to files function
updateStatistics()
{
  # data statistics
	for filename in ${FileNames[@]}
	do
		while read ID	Name Height  Result	NgType Time
		do 
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
		done <$filename
	done

# statistics resualt ok data
	for (( i=0; i<PARTNAME_COUNT; i++ ))
	do
		okpercent=$(echo "scale=4; ${okcnt[$i]} / ${partcnt[$i]} * 100" | bc)
		if [ $(echo "$okpercent < ${WARNING_THRESHOLD}" | bc) == 1 ]
		then
      # title
			printf "%-6s%-8s%-15s%-15s%-15s\n" "Name"	"OK(%)" \
				 "HEIGTH(MAX)" "HEIGTH(MIN)" "HEIGTH(Avg)" > ${REALTIMEFILENAME}

			avgheight[$i]=$(echo "scale=2;${tempheightsum[$i]} / ${partcnt[$i]}" | bc)

      # write data
			printf "%-6s%-8.2f%-15.2f%-15.2f%-15.2f\n" ${PARTNAME_ARRAY[$i]} $okpercent \
				 ${maxheight[$i]} ${minheight[$i]} ${avgheight[$i]} >> ${REALTIMEFILENAME}
			break
		fi
	done
}

#########################run Statistics and file create functions#######################

cd $shell_path   # switch the director to shell file position 

findFileNames

updateStatistics

#########################################compression data################################

tar -cjvf $(date +"%Y%m%d%H%M%S").tar.bz2 ${COMPFILEDIRETOR}{1,2} >/dev/null

exit 0

