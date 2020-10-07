div=65
for var in `seq 1 6`
do
	num=`expr $RANDOM % $div`
	echo $num
done
