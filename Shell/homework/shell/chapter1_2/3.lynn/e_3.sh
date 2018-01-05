#! /bin/bash
string1="monday tuesday wednesday"
for var in $string1
do
	echo "$var" >> ref.txt
done
string2="perfect"
printf "${string2}!!!!!!good!" >> ref.txt
string3="/home/augus/"
echo -e "\n$string3" >> ref.txt
echo -e "变量为string1,值为mondat tuesdy wednesday \n用单引号输出变量：" >> ref.txt
echo '$string1' >> ref.txt
echo "用双引号输出变量" >> ref.txt
echo "$string1" >> ref.txt
echo "不加大括号输出变量+字符串abc" >> ref.txt
echo "$string1abc" >> ref.txt
echo "加大括号输出变量+字符串abc" >> ref.txt
echo "${string1}abc" >> ref.txt
