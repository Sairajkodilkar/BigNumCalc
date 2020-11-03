#include "eval.h"
enum precedence {LOW, BRACKET, EQUAL, BOOL, ADDSUB, MULDIV, MODULO};

int getprece(char ch){
	switch(ch){
		case '+': case '-':
			return ADDSUB;
			break;
		case '*': case '/':
			return MULDIV;
			break;
		case '%':
			return MODULO;
			break;
		case '(': case ')':
			return BRACKET;
			break;
		case '=':
			return EQUAL;
			break;
		case '<': case '>': case 'l': case 'g': 
		case 'e': case 'n':
			return BOOL;
			break;
		default:
			return LOW;
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

void cleanstrstack(strstack *sts){
	char *buf;
	while(!strisempty(sts)){
		buf = strpop(sts);
		free(buf);
	}
	return;
}  


/*TODO strstack is pending */
num eval(char *str){
	nstack numbers; //stack containing the numbers
	cstack operators; //stack containing the operators
	strstack addresses;
	char identifier[20] = "\0";
	char *temp;

	/* hashtable initialization */
	static int reinit = 0;
	static hashtable symbols;
	if(reinit == 0){
		inithash(&symbols);
		reinit = 1;
	}

	token t;
	num result, one, two, error, noprint;
	static int prevtype;
	int currtype;

	int currpre = LOW, prevpre;
	char op, x;
	int printflag = 1;

	initnum(&one);
	initnum(&two);

	initnstack(&numbers);
	initcstack(&operators);
	initstrstack(&addresses);

	error.sign = 2;
	noprint.sign = 3;

	while(1){
		t = parse(str);
		switch(t.type){
			case OPERATOR:
				currtype = OPERATOR;
				if(!cisempty(&operators)){
					x = cpop(&operators);
					cpush(&operators, x);
					prevpre = getprece(x);
				}
				else{ 
					prevpre = currpre;
				}
				currpre = getprece(t.data.op);
				if(currpre == EQUAL){
					// string_stack * , char * 
					if(identifier[0] == '\0' || prevtype != VAR){
						cleannstack(&numbers);
						cleancstack(&operators);
						cleanstrstack(&addresses);
						return error;
					}
					cpush(&operators, t.data.op);
					strpush(&addresses, identifier);
					identifier[0] = '\0';
					prevtype = currtype;
				}
				else if(currpre == BRACKET && t.data.op == '('){
					cpush(&operators, t.data.op);
					prevtype = currtype;
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
								result = divide(one, two);
							case '%':
								break;
							case '<':
								result = lessthan(one, two);
								break;
							case '>':
								result = greaterthan(one, two);
								break;
							case 'l': //specifies less than equal
								result = lessthaneq(one, two);
								break;
							case 'g': //specifies greater than equal
								result = greaterthaneq(one, two);
								break;
							case 'e': //specifies equal
								result = equal(one, two);
								break;
							case 'n':
								result = notequal(one, two);
								break;
							case '=':
								if(strisempty(&addresses)){
									cleannstack(&numbers);
									cleancstack(&operators);
									return error;
								}
								strcpy(identifier, temp = strpop(&addresses)); //address is fetch which is string here;
								free(temp);
								insertnum(&symbols, identifier, two); //the number is stored at that address;
								initnum(&one); //as one would be garbage
								copy(two, &result);
								break;
							default:
								prevtype = currtype;
								cleannstack(&numbers);
								cleancstack(&operators);
								cleanstrstack(&addresses);
								return error;
								break;
						}
						erasenum(&two);
						erasenum(&one);
						initnum(&two);
						initnum(&one);
						npush(&numbers, result);
					}
					prevtype = currtype;
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
							result = divide(one, two);
							break;
						case '%':
							break;
						case '<':
							result = lessthan(one, two);
							break;
						case '>':
							result = greaterthan(one, two);
							break;
						case 'l': //specifies less than equal
							result = lessthaneq(one, two);
							break;
						case 'g': //specifies greater than equal
							result = greaterthaneq(one, two);
							break;
						case 'e': //specifies equal
							result = equal(one, two);
							break;
						case 'n':
							result = notequal(one, two);
							break;
						default:
							cleannstack(&numbers);
							cleancstack(&operators);
							cleanstrstack(&addresses);
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
				break;
				prevtype = currtype;

			case NUMBER:
				currtype = NUMBER;
				npush(&numbers, t.data.number);
				prevtype = currtype;
				break;

			case END:
				currtype = END;
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
							result = divide(one, two);
							break;
						case '<':
							result = lessthan(one, two);
							break;
						case '>':
							result = greaterthan(one, two);
							break;
						case 'l': //specifies less than equal
							result = lessthaneq(one, two);
							break;
						case 'g': //specifies greater than equal
							result = greaterthaneq(one, two);
							break;
						case 'e': //specifies equal
							result = equal(one, two);
							break;
						case 'n':
							result = notequal(one, two);
							break;
						case '=':
							if(strisempty(&addresses)){
								prevtype = currtype;
								cleannstack(&numbers);
								cleancstack(&operators);
								return error;
							}
							strcpy(identifier, temp = strpop(&addresses)); //address is fetch which is string here;
							free(temp);
							insertnum(&symbols, identifier, two); //the number is stored at that address;
							copy(two, &result);
							printflag = 0;
							break;
						default:
							cleannstack(&numbers);
							prevtype = currtype;
							cleancstack(&operators);
							return error;
							break;
					}
					npush(&numbers, result);
					erasenum(&two);
					erasenum(&one);
					initnum(&two);
					initnum(&one);
				}
				prevtype = currtype;
				if(printflag){
					return npop(&numbers);
				}
				else{
					return noprint;
				}
				break;

			case VAR:
				currtype = VAR;
				strcpy(identifier, t.data.var);
				one = search(symbols, identifier); //fetch the value 
				if(one.sign == error.sign)
					initnum(&one);
				npush(&numbers, one); //push it on numbers
				prevtype = currtype;
				break;

			case ERR:
				currtype = ERR;
				cleannstack(&numbers);
				cleancstack(&operators);
				cleanstrstack(&addresses);
				prevtype = currtype;
				return error;
				break;

			default:
				cleannstack(&numbers);
				cleancstack(&operators);
				cleanstrstack(&addresses);
				return error;
				break;
		}
	}
}




