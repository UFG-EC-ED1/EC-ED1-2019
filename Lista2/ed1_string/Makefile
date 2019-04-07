CC=gcc
LIBS=

all: main

main.o: main.c
	$(CC) -c main.c

main: ed1_string.o main.o
	$(CC) ed1_string.o main.o -o main

ed1_string.o: ed1_string.c ed1_string.h
	$(CC) -c ed1_string.c

munit.o: munit/munit.c
	$(CC) -c munit/munit.c

ed1_string_test.o: ed1_string_test.c
	$(CC) -c ed1_string_test.c

ed1_string_test: ed1_string_test.o ed1_string.o munit.o
	$(CC) $(LIBS) ed1_string_test.o ed1_string.o munit.o -o ed1_string_test

test: ed1_string_test
	./ed1_string_test

clean:
	rm -f ed1_string.o main.o main
	rm -f munit.o ed1_string_test.o ed1_string_test
