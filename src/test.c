#include "eval.h"
#include "hash.h"

int main(){
	hashtable table;
	inithash(&table);

	num one;
	initnum(&one);
	insert_digit(&one, 100);

	insertnum(&table, "sairaj", one);
	printnum(search(table, "sairaj"));
}
