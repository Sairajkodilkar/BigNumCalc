SOURCE=num.c parse.c nstack.c cstack.c eval.c main.c
OBJECT=num.o parse.o nstack.o cstack.o eval.o main.o
HEADER=parse.h num.h nstack.h cstack.h 

calc:$(OBJECT)
	$(CC) $^ -o $@

OBJECT:$(SOURCE)

%.o:%.c $(HEADER)
	$(CC) -c -Wall -g $<

clean:
	rm *\.gch *\.o calc

