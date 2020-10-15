SOURCE=num.c parse.c main.c
OBJECT=num.o parse.o main.o
HEADER=parse.h num.h

calc:$(OBJECT)
	$(CC) $^ -o $@

OBJECT:$(SOURCE)

%.o:%.c $(HEADER)
	$(CC) -c -Wall -g $^

clean:
	rm *.gch $(OBJECT) calc

