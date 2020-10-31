/* 
 * Data structure for number
 */


#ifndef _NUM
#define _NUM

#include <stdio.h>
#include <stdlib.h>

// Max digit length in one node

#define DIG_LEN 8 
#define MAX_DIG 99999999




#define MALLOCNODE ((node *)malloc(sizeof(node)))

typedef struct node{
	int digit;
	struct node *next;
}node;

typedef struct num{
	node *part;
	int point;
	int count;
	int sign;
}num;

void initconstants();

void initnum(num *one);
void insert_digit(num *one, int dig);
void printnum(num one);
void erasenum(num *one);
void reverse(num *one);
void copy(num source, num *dest);
int isgreater(num one, num two);
/* operators */
num add(num one, num two);
num sub(num one, num two);
num multiply(num one, num two);
num divide(num one, num two);
num equal(num one, num two);
num notequal(num one, num two);
num greaterthan(num one, num two);
num greaterthaneq(num one, num two);
num lessthan(num one, num two);
num lessthaneq(num one, num two);


#endif 



