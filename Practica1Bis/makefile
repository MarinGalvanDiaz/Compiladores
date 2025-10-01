# Makefile simple para calculadora de vectores

all: vector

vector: vector.tab.c
	gcc vector.tab.c -o vector -lm

vector.tab.c: vector.y
	yacc vector.y -o vector.tab.c

clean:
	rm -f vector vector.tab.c

run: vector
	./vector

.PHONY: all clean run
