#! /bin/bash
#one
printf "The bash version is : $BASH_VERSION" >> 2.txt 
printf "\nDisplay's name is: $DISPLAY" >> 2.txt 
printf "\nThe Home is: $HOME" >> 2.txt 
#two
let a=3
let b=7
let var=a+b
printf "\na+b=%d" $var >> 2.txt
c=$PATH
printf "\nThe PATH is :%s" $c >> 2.txt
name=gr
age=20
income=100
printf "\n姓名:%s 年龄:%d 收入:%.2f" $name $age $income >> 2.txt
#three
str="I AM A CHINESE"
for var in "$str"
do
  printf "\n%s" $var >> 2.txt
done
var=6
printf "\nHis English level is CET$var" >> 2.txt
PH=/home/grace/1.txt
printf "\nThe path is set to /home/grace/1.txt\n" >> 2.txt
IFS='/'
printf "%s" $PH >> 2.txt
#"" & ''
i=10
printf "\ni is deifined as 10 echo \"\" result is "$i" echo '' result is '$i'" >> 2.txt

IFS='\' >> ref.txt
echo "\\\"" >> ref.txt
echo '\\\' >> ref.txt
echo "'i'" >> ref.txt
echo '"i"' >> ref.txt

