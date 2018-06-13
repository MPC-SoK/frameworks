#!/bin/bash

#mpc.exe
#usage: mpc.exe <server_port> <num_parties> <address_file> <self_id> <num_and_gates>

./cleanup.sh

if [ -f "examples/$1" ]
then
	script="examples/$1"	
else
	script="examples/mill.wy"	
fi

echo "Running test $script"

screen -S wysteria -t mainTab -A -d -m
screen -S wysteria -X screen -t server0
screen -S wysteria -X screen -t server1
screen -S wysteria -X screen -t server2
screen -S wysteria -p server0 -X stuff $'mpc.exe 9000 3 addresses.txt 0 10000\n'
screen -S wysteria -p server1 -X stuff $'mpc.exe 9001 3 addresses.txt 1 10000\n'
screen -S wysteria -p server2 -X stuff $'mpc.exe 9002 3 addresses.txt 2 10000\n'
sleep 2

screen -S wysteria -X screen -t client0
screen -S wysteria -X screen -t client1
screen -S wysteria -X screen -t client2

screen -S wysteria -p client0 -X stuff $"wysteria --i-am \!Alice --gmw-port 9000 $script"$'\n'
screen -S wysteria -p client1 -X stuff $"wysteria --i-am \!Bob --gmw-port 9001 $script"$'\n'
screen -S wysteria -p client2 -X stuff $"wysteria --i-am \!Charlie --gmw-port 9002 $script"$'\n'
sleep 2

