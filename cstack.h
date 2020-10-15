#include <stdio.h>

/* stack for char data type using linkedlist */

typedef struct cnode{
	char ch;
	struct cnode *next;
}cnode;

typedef struct cnode *cstack;

void initcstack(cstack *);
int nisempty(cstack *);
int nisfull(cstack *);
char npop(cstack *);
void npush(cstack *, char );

