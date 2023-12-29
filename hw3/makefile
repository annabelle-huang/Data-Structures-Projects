
# makefile
# Annabelle Huang
# CPSC 223 HW 3
# March 10th, 2023
# Purpose: provide shortcuts for running command line scripts 
#          for hookbook
CC = gcc
CFLAGS = -std=c17 -Wall -Werror -pedantic -g 

.RECIPEPREFIX = >

.PHONY: clean

HookBook: hookbook.o 
>${CC} ${CFLAGS} -o $@ $^

hookbook.o: hookbook.c pirate_list.h pirate.h pirate_list.c

pirate_list.o: pirate_list.c pirate_list.h pirate.h

clean:
>rm -f *.o HookBook
