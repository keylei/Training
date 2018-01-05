#!/bin/bash  
  
echo -n Count:  
tput sc  
  
count=0  
while true;  
do  
        if [ $count -lt 10 ];then  

                let count++;  
                read input
                sleep 1;  
                tput rc  
                tput ed  
                echo -n $count; 
 
        else  
                echo give up to mv a.txt to b.txt.
                exit 0;  
        fi  
done  











 

