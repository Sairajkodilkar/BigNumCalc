#include "hash.h"

void inithash(hashtable *h){
	int i;
	*h = (num_node **)malloc(sizeof(num_node *) * SIZE_T);
	for(i = 0; i < SIZE_T; i++){
		(*h)[i] = NULL;
	}
	return;
}

int hashfuct(char *str){
	int i = 0, k = 0, l = strlen(str);
	for(i = 0; i < l; i++){
		k += (int)str[i] * (i + 1); //weighted sum is considered 
	}
	return k % SIZE_T;
}

	
void insertnum(hashtable *h, char *str, num x){
	int index, flag = 1;
	num one;
	/* copy of num is stored not actual so erasing actual num does not erase this */
	initnum(&one);
	copy(x, &one);
	num_node *temp;
	index = hashfuct(str);

	if((*h)[index] != NULL){
		temp = (*h)[index];

		while(temp->next != NULL){
			if(strcmp(temp->string, str) == 0){
				erasenum(&(temp->one));
				temp->one = one;
				flag = 0;
				break;
			}
			temp = temp->next;
		}
		if(flag && strcmp(temp->string, str) == 0){
			erasenum(&(temp->one));
			temp->one = one;
			flag = 0;
		}
		if(flag){
			temp->next = (num_node *)malloc(sizeof(num_node));
			temp = temp->next;
			strcpy(temp->string, str);
			temp->one = one;
			temp->next = NULL;
		}
	}
	else{
		(*h)[index] =  (num_node *)malloc(sizeof(num_node));
		temp = (*h)[index];
		strcpy(temp->string, str);
		temp->one = one;
		temp->next = NULL;
	}
	return;
}

num search(hashtable h, char *str){
	int key;
	num_node *temp;
	num error;
	num one;
	initnum(&error);
	error.sign = 2;

	key = hashfuct(str);
	temp = h[key];

	while(temp != NULL){
		if(strcmp(temp->string, str) == 0){
			/* copy is returned so even if user destroys number it does not affect this */
			copy(temp->one, &one);
			return one;
		}
		temp = temp->next;
	}
	return error;
}




















