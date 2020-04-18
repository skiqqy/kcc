### Makefile for kcc project ###
COMP=gcc
FLAGS= -Wall -pedantic
SCANNER_E=bin/scanner

clean:
	rm -rf bin
	rm -rf obj

install:
	mkdir -p obj
	mkdir -p bin

scanner: install
	$(COMP) $(FLAGS) -o $(SCANNER_E) src/scanner.c
