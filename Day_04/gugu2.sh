for i in `seq 1 9`
do
	echo == $i 단 ==
	for j in `seq 1 9`
	do
		echo $i x $j = $((i*j))
	done
done
