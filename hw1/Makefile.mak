CC=gcc
CFLAGS= -std=c99 -g3 -Wall -pedantic 

.PHONY: clean

Hello: Hello.o
	${CC} ${CFLAGS} -o $@ $^

Hello.o: Hello.c 

clean:
	rm -f *.o Hello 
