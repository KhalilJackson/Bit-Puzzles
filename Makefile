#
# Makefile for btest
# 
CC = gcc
CFLAGS = -O -Wall -m32
LIBS = -lm

all: btest

btest: btest.c puzzles.c decl.c tests.c btest.h puzzles.h
	$(CC) $(CFLAGS) $(LIBS) -o btest puzzles.c btest.c decl.c tests.c

btestexplicit:
	$(CC) $(CFLAGS) $(LIBS) -o btest puzzles.c btest.c decl.c tests.c 

clean:
	rm -f *.o btest *~

