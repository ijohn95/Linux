a.out : run.o main.o
	gcc -o a.out run.o main.o

run.o : run.c
	gcc -c -o run.o run.c

main.o : main.c
	gcc -c -o main.o main.c

clean :
	rm *.o a.out
