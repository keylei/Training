#!/bin/bash

# shell name
shfilename=4_archiving.sh

# get the target shell path
shpath="$(cd `dirname $0`; pwd)/${shfilename}"

# config the timing tast
crontab -l > /tmp/crontab.$$ >/dev/null 2>&1

# find if there have a same tast
if [ $? == 0 ]
then
	while read line
	do 
		local tempdata=${line##*/}                     # remove the path from the full file name
		[ "$tempdata" == "$shfilename" ] && { exit 1; }
	done < /tmp/crontab.$$
fi

echo "*/1 * * * * ${shpath}" >> /tmp/crontab.$$    # write the task

crontab /tmp/crontab.$$


exit 0

