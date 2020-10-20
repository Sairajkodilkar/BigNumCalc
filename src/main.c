#include <stdio.h>
#include "eval.h"
#include "read.h"

/* currently operate on int */


int main(){
	num result; 
	int i; 
	int size;
	char buf[1000] = "1111111111111111111111111111111111111111111.11111111111111111 + 11111111111111111111111111111111";

	//while(1){
	/*
		if((readline(&buf, &size)) == 0 || buf[0] == '\n' || buf[0] == EOF){
			return 0;
		}
		*/

		result = eval(buf);

		if(result.sign == 2){
			printf("BAD EXPRESSION\n");
		}
		printnum(result);
		erasenum(&result);
		//free(buf);
	//}
}


