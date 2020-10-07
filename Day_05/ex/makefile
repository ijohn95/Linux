#CC = gcc
CFLAGS = -g -O2 -Wall
SRCS = test1.c test2.c test3.c test4.c
OBJS = $(SRCS:.c=.o)

test: $(OBJS)
	$(CC) -o $@ $^

.c.o:
	$(CC) -c $(CFLAGS) $<

clean : 
	rm $(OBJS) test

dep:
	gccmakedep $(SRCS)
