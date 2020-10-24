#include "eval.h"
enum precedence {LOW, BRACKET, EQUAL, ADDSUB, MULDIV, MODULO};

int getprece(char ch){
	switch(ch){
		case '+': case '-':
			return ADDSUB;
		case '*': case '/':
			return MULDIV;
		case '%':
			return MODULO;
		case '(': case ')':
			return BRACKET;
		case '=':
			return EQUAL;
	}
	return LOW;
}

void cleannstack(nstack *numbers){
	num one;
	while(!nisempty(numbers)){
		one = npop(numbers);
		erasenum(&one);
	}
	return;
}

void cleancstack(cstack *op){
	while(!cisempty(op)){
		cpop(op);
	}
	return;
}

/* todo division operation is pending */
num eval(char *str){
	nstack numbers; //stack containing the numbers
	cstack operators; //stack containing the operators
	cstack address; //stack containing memory addresses where result must be store

	static num memory[26] = { 0 }; //memory addresses to store a-z variables
	static int storage;

	token t;
	num result, one, two, error, noprint;

	int currpre = LOW, prevpre;
	char op;
	int printflag = 1;

	initnum(&one);
	initnum(&two);
	initnstack(&numbers);
	initcstack(&operators);
	initcstack(&address);

	error.sign = 2;
	noprint.sign = 3;

	while(1){
		t = parse(str);
		switch(t.type){
			case OPERATOR:
				prevpre = currpre;
				currpre = getprece(t.data.op);
				////printf("op %c\n", t.data.op);
				if(currpre == EQUAL){
					//printf("pushed %c with storage %d \n", t.data.op, storage);
					cpush(&address, (char)storage);
					cpush(&operators, t.data.op);
					break;
				}
				if(currpre == BRACKET && t.data.op == '('){
					cpush(&operators, t.data.op);
					break;
				}
				else if(currpre == BRACKET && t.data.op == ')'){
					while((op = cpop(&operators)) != '('){
						two = npop(&numbers);
						one = npop(&numbers);
						switch(op){
							case '+':
								result = add(one, two);
								break;
							case '-':
								result = sub(one, two);
								break;
							case '*':
								result = multiply(one, two);
								break;
							case '/':
								break;
							case '%':
								break;
							case '=':
								//printf("copying\n");
								storage = (int)cpop(&address);
								copy(two, memory + storage);
								//printnum(memory[storage]);
								//printnum(two);
								printflag = 0;
								break;
							default:
								//printf("yes\n");
								cleannstack(&numbers);
								return error;
								break;
						}
						erasenum(&two);
						erasenum(&one);
						initnum(&two);
						initnum(&one);
						//printf("here\n");
						npush(&numbers, result);
						//printf("here2\n");
					}
					//printf("outside\n");
					break;
				}
				else if(currpre < prevpre){
					//printf("nahi tikde\n");
					two = npop(&numbers);
					one = npop(&numbers);
					op = cpop(&operators);
					switch(op){
						case '+':
							result = add(one, two);
							break;
						case '-':
							result = sub(one, two);
							break;
						case '*':
							result = multiply(one, two);
							break;
						case '/':
							break;
						case '%':
							break;
						default:
							cleannstack(&numbers);
							return error;
							break;
					}
					npush(&numbers, result);
					cpush(&operators, t.data.op);
					erasenum(&two);
					erasenum(&one);
					initnum(&two);
					initnum(&one);
					break;
				}
				else{
					////printf("%c\n", t.data.op);
					cpush(&operators, t.data.op);
					break;
				}
			case NUMBER:
				npush(&numbers, t.data.number);
				break;

			case END:
				printf("ending \n");
				while(!cisempty(&operators)){
					//printf("ending while\n");
					two = npop(&numbers);
					one = npop(&numbers);
					op = cpop(&operators);
					switch(op){
						case '+':
							result = add(one, two);
							break;
						case '-':
							result = sub(one, two);
							break;
						case '*':
							result = multiply(one, two);
							break;
						case '/':
							break;
						case '%':
							break;
						case '=':
							////printf("yes\n");
							storage = (int)cpop(&address);
							copy(two, memory + storage);
							printflag = 0;
							break;
						default:
							cleannstack(&numbers);
							return error;
							break;
					}
					npush(&numbers, result);
					erasenum(&two);
					erasenum(&one);
					initnum(&two);
					initnum(&one);
				}
				if(printflag){
					printf("printflag 1\n");
					return npop(&numbers);
				}
				else{
					printf("printflag = 0\n");
					return noprint;
				}
				break;

			case VAR:
				storage = t.data.op - 'a';
				copy(memory[storage], &one); //fetch value and make a copy
				////printf("copy succ\n");
				npush(&numbers, one); //push it on numbers
				break;

			case ERR:
				cleannstack(&numbers);
				return error;
				break;


			default:
				cleannstack(&numbers);
				return error;
				break;

		}
	}
}




