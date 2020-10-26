SOURCE=num.c parse.c nstack.c cstack.c eval.c read.c main.c
OBJECT=num.o parse.o nstack.o cstack.o eval.o read.o main.o
HEADER=parse.h num.h nstack.h cstack.h read.h eval.h
CFLAG=-c -Wall  -I include 

vpath %.c src 
vpath %.h include

calc:$(OBJECT) 
	$(CC) $^ -o $@

OBJECT:$(SOURCE) 

%.o:%.c $(HEADER) Makefile
	$(CC) $(CFLAG) $<

clean:
	rm *\.o calc

