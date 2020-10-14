#include <stdio.h>
#include "num.h"
#include "parse.h"

/* currently operate on int */

int main(){
	token t;
	num one, two, result;
	initnum(&one);
	initnum(&two);
	initnum(&result);
	int j = 0;

	while(1){
		t = parse("1111111111111111 * 111111111111");
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

	result = multiply(one, two);
	//result = add(one, two);
	
	printnum(one);
	printnum(two);
	printnum(result);
	
}

