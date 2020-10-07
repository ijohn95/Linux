input=$1

echo == $input 단 ==
for j in `seq $2 $3`
do
	echo $input x $j = $((input*j))
done
