#include "strstack.h"

/* stack for string data type using linkedlist */

void initstrstack(strstack *n){
	*n = NULL;
	return;
}

int strisfull(strstack *n){
	//as it is never full
	return 0;
}

int strisempty(strstack *n){
	return (*n) == NULL;
}


void strpush(strstack *n, char *str){
	if(strisfull(n))
		return;
	strnode *new;
	new = (strnode *) malloc(sizeof(strnode));
	new->string = (char *)malloc(strlen(str)); 
	strcpy(new->string, str);
	new->next = (*n);
	(*n) = new;
}

char *strpop(strstack *n){
	char *str;
	strnode *temp;
	if(strisempty(n))
		return NULL;
	str = (*n)->string;
	temp = (*n);
	(*n) = (*n)->next;
	free(temp);
	return str;
}

	
