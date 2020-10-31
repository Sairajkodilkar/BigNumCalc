#include "eval.h"
#include "hash.h"

int main(){
	hashtable table;
	inithash(&table);

	num one;
	initnum(&one);

	insert_digit(&one, 100);
	insertnum(&table, "sairaj", one);
	insert_digit(&one, 100);
	printnum(one);
	insertnum(&table, "sajrai", one);
	printnum(search(table, "sajrai"));
	printnum(search(table, "sairaj"));
	printnum(one);
}
