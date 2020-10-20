#include <stdio.h>
#include "eval.h"
#include "read.h"

/* currently operate on int */


int main(){
	num result; 
	char buf[1000];
	int i;
	i = readline(buf, 1000);
	result = eval(buf);
	if(result.sign == 2){
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
		t = parse("111122221123746019324713204978103297411.1112341234132412342134111111111 - 1111112.34123412341234123413241234111");
		//t = parse("1111111111111 * 1111111111111");
		//t = parse("123456.78912312345 * 122.347");
		if(t.type == NUMBER){
			if(j == 0){
				one = t.data.number;
				j++;
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
	}

	//printf("count is %d %d\n", one.point, two.point);
	//printnum(one);

	//result = multiply(one, two);
	
	//printf("%d\n", isgreater(one, two));
	
	result = sub(one, two);
	printnum(one);
	printnum(two);
	printnum(result);
	

}
*/
