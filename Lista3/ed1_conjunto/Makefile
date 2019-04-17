all: test

test: conjunto_test
	./conjunto_test

conjunto.o: conjunto.c conjunto.h
	gcc -c conjunto.c

conjunto_test.o: conjunto_test.c conjunto.h
	gcc -c conjunto_test.c

conjunto_test: conjunto_test.o conjunto.o
	gcc conjunto_test.o conjunto.o -o conjunto_test

clean:
	rm -fv conjunto_test conjunto_test.o conjunto.o

