keepThese=("addresses.txt" "princs.txt")

#If a screen session named wysteria exists, kill it
if [[ `screen -ls | grep wysteria | wc -l` -gt 0 ]]
then
	#screen -d wysteria
	screen -S wysteria -X quit
fi

#Delete all the temporary files created by the mpc.exe and wysteria.exe
for f in *.txt
do
	if [[ ! " ${keepThese[@]} " =~ " ${f} " ]]; then
		rm -f "$f"
	fi
done

# remove possibly generated data files
rm -f "data/accum"

for f in *.smt
do
	rm -f "$f"
done

# close any remaining open ports
for pid in `ps aux | grep mpc.exe | grep -v grep | awk '{print $2}'`
do
  kill $pid
done

