### Makefile for kcc project ###
COMP=gcc
FLAGS= -Wall -pedantic
SCANNER_E=bin/testscanner
COMPN=bin/kcc

all: scanner.o
	$(COMP) $(FLAGS) -o $(COMPN) src/kcc.c obj/*.o

clean:
	rm -rf bin
	rm -rf obj

install:
	mkdir -p obj
	mkdir -p bin

testscanner: install scanner.o
	$(COMP) $(FLAGS) -o $(SCANNER_E) src/testscanner.c obj/scanner.o

scanner.o: install
	$(COMP) $(FLAGS) -c -o obj/scanner.o src/scanner.c
