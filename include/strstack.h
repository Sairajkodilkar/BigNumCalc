#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* stack for string data type using linkedlist */

typedef struct strnode{
	char *string;
	struct strnode *next;
}strnode;

typedef struct strnode *strstack;

void initstrstack(strstack *);
int strisempty(strstack *);
int strisfull(strstack *);
/* user need to free the string after using */
char *strpop(strstack *);
void strpush(strstack *, char *);

