#include <stdio.h>
#include <stdlib.h>
#include "num.h"

/* stack for number data type using linkedlist */

typedef struct nnode{
	num one;
	struct nnode *next;
}nnode;

typedef struct nnode *nstack;

void initnstack(nstack *);
int nisempty(nstack *);
int nisfull(nstack *);
num npop(nstack *);
void npush(nstack *, num );

