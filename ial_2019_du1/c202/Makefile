
PRJ=c202
#
PROGS=$(PRJ)-test
CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -lm

all: $(PROGS) $(PRJ)-advanced-test

$(PRJ)-test: $(PRJ).c $(PRJ)-test.c
	$(CC) $(CFLAGS) -o $@ $(PRJ).c $(PRJ)-test.c

$(PRJ)-advanced-test: $(PRJ).c $(PRJ)-advanced-test.c
	$(CC) $(CFLAGS) -o $@ $(PRJ).c $(PRJ)-advanced-test.c

clean:
	rm -f *.o *.out $(PROGS)
#
