#include <stdio.h>
#include "eval.h"
#include "read.h"

/* currently operate on int */


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


