#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "num.h"

#define SIZE_T 100

typedef struct num_node{
	char string[20];
	num one;
	struct num_node *next;
}num_node;

typedef num_node** hashtable;

void inithash(hashtable *);
void insertnum(hashtable *, char *str, num one);
num search(hashtable , char *str);


