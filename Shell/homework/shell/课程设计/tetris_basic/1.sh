#!/bin/bash


#!/bin/bash

PASSWORD(){
ifs=$IFS
IFS=
read -s -n 1 line

echo $line

case $line in

"")
        echo "Enter"
#        echo "Your password is [$a]"       
        ;;

*)
        echo "Space"
#        a="${a}${line}"
#        PASSWORD
        ;;
esac
IFS=$ifs
}

echo -n "password:"
PASSWORD

