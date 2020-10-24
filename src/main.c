#include <stdio.h>
#include "eval.h"
#include "read.h"


int main(){
	num result; 
	int size;
	int x;
	char *buf;

	while(1){
	
		if((x = readline(&buf, &size)) == 0){
			continue;
		}

		if(x == EOF)
			return 0;

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
