/* 
 * Data structure for number
 */


#ifndef _NUM
#define _NUM

#include <stdio.h>

// Max digit length in one node
#define DIG_LEN 8 

#define MALLOCNODE ((node *)malloc(sizeof(node)))

typedef struct node{
	int digit;
	struct node *next;
}node;

typedef struct num{
	node *part;
	int point;
	int sign;
}num;

void initnum(num *one);
void insert_digit(num *one, int dig);
num add(num one ,num two);
num sub(num one, num two);
num multiply(num one, num two);
num divide(num one, num two);

#endif 



