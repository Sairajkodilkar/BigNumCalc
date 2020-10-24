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
				if(currpre == EQUAL){
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
								storage = (int)cpop(&address);
								copy(two, memory + storage);
								printflag = 0;
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
						case '=':
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
					return npop(&numbers);
				}
				else{
					return noprint;
				}
				break;

			case VAR:
				storage = t.data.op - 'a';
				copy(memory[storage], &one); //fetch value and make a copy
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




