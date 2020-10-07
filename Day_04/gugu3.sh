input=$1

echo == $input 단 ==
for j in `seq 1 9`
do
	echo $input x $j = $((input*j))
done
