PRJ=c204
#
C202PATH=../c202/
PROGS=$(PRJ)-test
CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -lm -I$(C202PATH)

all: $(PROGS) $(PRJ)-advanced-test

$(PRJ)-test: $(PRJ).c $(PRJ)-test.c $(C202PATH)c202.c
	$(CC) $(CFLAGS) -o $@ $(PRJ).c $(PRJ)-test.c $(C202PATH)c202.c

$(PRJ)-advanced-test: $(PRJ).c $(PRJ)-advanced-test.c $(C202PATH)c202.c
	$(CC) $(CFLAGS) -o $@ $(PRJ).c $(PRJ)-advanced-test.c $(C202PATH)c202.c

clean:
	rm -f *.o *.out $(PROGS)
#
