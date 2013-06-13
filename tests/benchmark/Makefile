CC=gcc
CFLAGS=-O3 -Wall -I.
LFLAGS=-lpthread -ldl -llttng-ust -Wl,--no-as-needed

all: bench1 bench2

bench1: bench.c
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

bench2: bench.c tp.o
	$(CC) $(CFLAGS) $(LFLAGS) -DTRACING -o $@ $^

tp.o: tp.c ust_tests_benchmark.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -f *.o bench1 bench2
