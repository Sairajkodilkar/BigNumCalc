#include <stdio.h>
#include "eval.h"
#include "read.h"



/*
int main(){
	num result; 
	int size;
	char *buf;

	while(1){
	
		if((readline(&buf, &size)) == 0 || buf[0] == '\n' || buf[0] == EOF){
			return 0;
		}

		result = eval(buf);

		if(result.sign == 2){
			printf("BAD EXPRESSION\n");
		}
		else{
			printnum(result);
			erasenum(&result);
		}
		free(buf);
	}
}
*/


int main(){
	token t;
	num one, two, result;
	initnum(&one);
	initnum(&two);
	initnum(&result);
	int j = 0;
	char ch;

	while(1){
		//t = parse("111122221123746019324713204978103297411.1112341234132412342134111111111 - 1111112.34123412341234123413241234111");
		t = parse("112302394.874103478");
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
		if(t.type == VAR){
			printf("var %c\n", t.data.op);
		}
		if(t.type == END)
			break;
		if(t.type == OPERATOR)
			printf("op %c\n", t.data.op);
	}

	//printf("count is %d %d\n", one.point, two.point);
	//printnum(one);

	//result = multiply(one, two);
	
	//printf("%d\n", isgreater(one, two));
	
	//result = sub(one, two);
	copy(one, &result);
	erasenum(&one);
	printnum(result);
	//printnum(two);
	//printnum(result);
	

}
