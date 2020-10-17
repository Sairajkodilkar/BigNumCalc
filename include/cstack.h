#include <stdio.h>
#include <stdlib.h>

/* stack for char data type using linkedlist */

typedef struct cnode{
	char ch;
	struct cnode *next;
}cnode;

typedef struct cnode *cstack;

void initcstack(cstack *);
int cisempty(cstack *);
int cisfull(cstack *);
char cpop(cstack *);
void cpush(cstack *, char );

