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
			continue;
		}
		else if(result.sign == 3){
			continue;
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
		t = parse("sairaj");
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
			printf("var %s\n", t.data.var);
		}
		if(t.type == END)
			break;
		//if(t.type == OPERATOR)
			//printf("op %c\n", t.data.op);
	}

	//printf("count is %d %d\n", one.point, two.point);
	//printnum(one);

	//result = multiply(one, two);
	
	//printf("%d\n", isgreater(one, two));
	
	//result = divide(two, one);
	//printnum(two);
	//printnum(result);
	//erasenum(&result);
	

}
