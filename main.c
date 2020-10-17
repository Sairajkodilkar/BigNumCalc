#include <stdio.h>
#include "eval.h"

/* currently operate on int */


int main(){
	num result;
	result = eval("( 111111111 - 111111111 )* 2");
	if(result.sign == 0){
		printf("bad expr\n");
		return 1;
	}
	printnum(result);
	erasenum(&result);
}







/*
int main(){
	token t;
	num one, two, result;
	initnum(&one);
	initnum(&two);
	initnum(&result);
	int j = 0;

	while(1){
		t = parse("123 * 123");
		if(t.type == NUMBER){
			if(j == 0){
				one = t.data.number;
			}
			else{
				two = t.data.number;
			}
		}
		if(t.type == END)
			break;
		if(t.type == OPERATOR)
			;
		//	printf("%c\n", t.data.op);
		j++;
	}

	//result = multiply(one, two);
	one.sign = -1;
	two.sign = 1;
	result = sub(one, two);
	
	printnum(one);
	printnum(two);
	printnum(result);
	
}
*/
