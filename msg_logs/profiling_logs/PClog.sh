#!/bin/bash

file="/home/pi/Documents/profiling_logs/Tlog$(date +%R).txt"
file2="/home/pi/Documents/NETlog$(date +%R).txt"

tshark -a duration:30 -i br0 -w $file2 &

echo "MEM, CPU" > $file
n=0
while [ $n -lt 240 ];
do
	MEM=$(free -m | awk 'NR==2{printf "%.2f%%, ", $3*100/$2}')
	CPU=$(top -bn1 | grep load | awk '{printf "%.2f%%", $(NF-2)}')
	echo "$MEM$CPU" >> $file
	sleep 0.25 
	let n+=1
done
