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


void cpush(cstack *n, char ch){
	if(cisfull(n))
		return;
	cnode *new;
	new = (cnode *) malloc(sizeof(cnode));
	new->ch = ch;
	new->next = (*n);
	(*n) = new;
}

char cpop(cstack *n){
	char ch;
	cnode *temp;
	if(cisempty(n))
		return '0';
	ch = (*n)->ch;
	temp = (*n);
	(*n) = (*n)->next;
	free(temp);
	return ch;
}

	
