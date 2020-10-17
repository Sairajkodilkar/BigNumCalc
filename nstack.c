#include "nstack.h"

/* stack for number data type using linkedlist */

void initnstack(nstack *n){
	*n = NULL;
	return;
}

int nisfull(nstack *n){
	//as it is never full
	return 0;
}

int nisempty(nstack *n){
	return (*n) == NULL;
}


void npush(nstack *n, num one){
	if(nisfull(n))
		return;
	nnode *new;
	new = (nnode *) malloc(sizeof(nnode));
	new->one = one;
	new->next = (*n);
	(*n) = new;
}

num npop(nstack *n){
	num one;
	nnode *temp;
	if(nisempty(n)){
		one.sign = 0;
		return one;
	}
	one = (*n)->one;
	temp = (*n);
	(*n) = (*n)->next;
	free(temp);
	return one;
}

	
