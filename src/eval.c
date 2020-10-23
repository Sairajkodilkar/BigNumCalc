#include "eval.h"
enum precedence {LOW, BRACKET, ADDSUB, MULDIV, MODULO};

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

/* todo division operation is pending */
num eval(char *str){
	nstack numbers;
	cstack operators;

	token t;
	num result, one, two, error;

	int currpre = LOW, prevpre ;
	static char op;

	initnum(&one);
	initnum(&two);
	initnstack(&numbers);
	initcstack(&operators);

	error.sign = 2;

	while(1){
		t = parse(str);
		switch(t.type){
			case OPERATOR:
				prevpre = currpre;
				currpre = getprece(t.data.op);
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
							default:
								cleannstack(&numbers);
								return error;
								break;
						}
						erasenum(&two);
						erasenum(&one);
						initnum(&two);
						initnum(&one);
						npush(&numbers, result);
					}
					break;
				}
				else if(currpre < prevpre){
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
					cpush(&operators, t.data.op);
					break;
				}
			case NUMBER:
				npush(&numbers, t.data.number);
				break;

			case END:
				while(!cisempty(&operators)){
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
					erasenum(&two);
					erasenum(&one);
					initnum(&two);
					initnum(&one);
				}
				return npop(&numbers);
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




