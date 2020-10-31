SOURCE=cstack.c eval.c hash.c main.c nstack.c num.c parse.c read.c strstack.c 
OBJECT=cstack.o eval.o hash.o main.o nstack.o num.o parse.o read.o strstack.o 
HEADER=cstack.h  eval.h  hash.h  nstack.h  num.h  parse.h  read.h  strstack.h
CFLAG=-c -Wall -I include 

vpath %.c src 
vpath %.h include

calc:$(OBJECT) 
	$(CC) $^ -o $@

OBJECT:$(SOURCE) 

%.o:%.c $(HEADER) Makefile
	$(CC) $(CFLAG) $<

clean:
	rm *\.o calc

