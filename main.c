#include <stdio.h>
#include "num.h"
#include "parse.h"

/* currently operate on int */

int main(){
	token t;
	num one, two, result;
	int j = 0;

	while(1){
		t = parse("111111111 * 111111111");
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
		j++;
	}
	result = multiply(one, two);
	printnum(one);
	printnum(two);
	printnum(result);
}

