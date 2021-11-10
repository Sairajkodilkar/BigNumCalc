#include <stdio.h>
#include "eval.h"
#include "read.h"


int main(){
	num result; 
	int size;
	char *buf;
	initconstants();
	//printf("HIGH PRECISION CALCULATOR\npress CTRL-D to exit\n\n");

	while(1){

		//printf(">>> ");
		size = readline(&buf, &size); 

		if(size == 0){
			continue;
		}

		if(size == EOF){
			printf("\n");
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
