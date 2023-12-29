# makefile
# Annabelle Huang
# CPSC 223 HW 2
# February 11th, 2023
# Purpose: provide shortcuts for running command line scripts 
#          for program of life

CC=gcc
CFLAGS= -std=c99 -g3 -Wall -pedantic 

.PHONY: clean

Life: main.o Life.o
	${CC} ${CFLAGS} -o $@ $^ -lm

main.o: main.c Life.h

Life.o: Life.c Life.h

clean:
	rm -f *.o Life
