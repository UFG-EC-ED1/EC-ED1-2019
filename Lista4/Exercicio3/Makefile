CC=gcc


all: main test

lista_ordenada.o: lista_ordenada.c
	$(CC) -c lista_ordenada.c

main.o: main.c
	$(CC) -c main.c

test: main
	./main

main: lista_ordenada.o main.o
	$(CC) lista_ordenada.o main.o -o main

