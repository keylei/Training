#!/bin/bash

# define Running condition
SAVEFILENAME="search.txt"


# Define the global variable
declare -i timestamp_now                                 #save the timestap when input the search time
declare -i timestamp_start                               #save the start timestap which time we start
declare -a FileNames                                     #save the line1 and line2 file names


###############################functions###############################

# Find all files in directory line1 and line2 and filter with the time gap
filterFileNames()
{
	while read line
	do 
		local tempfilename1=${line##*/}          # remove the path from the full file name
		local temfile=${tempfilename1%.*}        # remove the file extension name 
		local timstr="${temfile:0:4}-${temfile:4:2}-${temfile:6:2} ${temfile:8:2}:${temfile:10:2}:${temfile:12:2}"  # change to std time formate
		local filename_timestamp=$(date -d "$timstr" +%s)  # get the timestamp
	  [ $timestamp_start -le $filename_timestamp ] && { FileNames[$indexCounter]=$line;let indexCounter+=1; }
	done < <(find "./Line1" "./Line2" -type f)
}

# Update statistics resualt and save to files function
searchFileData()
{
	local idcnt=0
  # title
	echo -e "Search data from $(date -d @$timestamp_start +"%F %T") to $(date -d @$timestamp_now +"%F %T")" > $SAVEFILENAME
	printf "%-5s%-6s%-10s%-10s%-15s%-25s \n" "ID"	"Name" "Height"  "Result"	"NgType" "Time" >> $SAVEFILENAME

  # data statistics
	for filename in ${FileNames[@]}
	do
		while read ID	Name Height  Result	NgType Time
		do
			[ ${ID} == "ID" ] && { continue; }
			local data_timestamp=$(date -d "$Time" +%s)
			if [ $timestamp_start -le $data_timestamp ]
			then
				let idcnt+=1
				printf "%-5s%-6s%-10.2f%-10s%-15s%-5s \n" $idcnt $Name $Height $Result $NgType "${Time}" >> $SAVEFILENAME
			fi
		done <$filename
	done
}



#########################get the input time gap parameter###########################

read -p	"Please input the time interval from now,the unit is second:"  timeinterval

[ "$(echo $timeinterval | bc 2>/dev/null)" != "$timeinterval" ] && \
		{ echo "Please input number,like：$MINDATA_COUNTS";exit 1;}            # judge if the input is an num

[ "$(echo $timeinterval | grep "\." >/dev/null)" != "" ] && \
		{ echo "Please input integer number,like：$MINDATA_COUNTS";exit 1; }   # judge if the input is an int num

timestamp_now=$(date +%s)                          # get now timestamp when input the sencond

let timestamp_start=$timestamp_now-$timeinterval   # calculate the start time timestamp

# show the time gap between now and the data create
echo -e "Search data from $(date -d @$timestamp_start +"%F %T") to $(date -d @$timestamp_now +"%F %T")"

################run Statistics and file create functions

filterFileNames

searchFileData

exit 0

