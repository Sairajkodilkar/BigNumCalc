#include "cstack.h"

/* stack for char data type using linkedlist */

void initcstack(cstack *n){
	*n = NULL;
	return;
}

int cisfull(cstack *n){
	//as it is never full
	return 0;
}

int cisempty(cstack *n){
	return (*n) == NULL;
}


void cpush(cstack *n, char one){
	if(isfull(n))
		return;
	cnode *new;
	new = (cnode *) malloc(sizeof(cnode));
	new->one = one;
	new->next = (*n);
	(*n) = new;
}

char cpop(cstack *n){
	char one;
	cnode *temp;
	if(isempty(n))
		return;
	one = (*n)->one;
	temp = (*n);
	(*n) = (*n)->next;
	free(temp);
	return one;
}

	
