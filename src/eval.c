#include "eval.h"

enum precedence {LOW, ADDSUB, MULDIV, MODULO, BRACKET};

void cleannstack(nstack *);

num eval(char *str){
	nstack numbers;
	cstack operators;

	token t;
	num result, one, two, error, warning;

	int currpre = LOW, prevpre, bracket = 0;
	char op;

	initnum(&one);
	initnum(&two);
	initnstack(&numbers);
	initcstack(&operators);

	error.sign = 2;
	warning.sign = 3;

	while(1){
		t = parse(str);
		switch(t.type){
			case OPERATOR:
				//printf("operator %c\n", t.data.op);
				prevpre = currpre;
				switch(t.data.op){
					case '+': case '-':
						//printf("inside\n");
						currpre = ADDSUB + bracket;
						break;
					case '*': case '/':
						currpre = MULDIV + bracket;
						break;
					case '%':
						currpre = MODULO + bracket;
						break;
					case '(':
						bracket += BRACKET;
						continue;
						break;
					case ')':
						bracket -= BRACKET;
						continue;
						break;
					default:
						return error;
				}
				if(currpre <= prevpre){
					//printf("inside checker \n");
					while(!cisempty(&operators)){
						op = cpop(&operators);

						if(nisempty(&numbers))
							return error;
						two = npop(&numbers);
						if(nisempty(&numbers))
							return error;
						one = npop(&numbers);

						switch(op){
							case '+':
								//printf("add\n");
								result = add(one, two);
								break;
							case '-':
								result= sub(one, two);
								break;
							case '*':
								result = multiply(one, two);
								break;
							case '/':
								//result = divide(one, two);
								break;
							case '%':
								//result = modulo(one, two);
								break;
							default:
								return error;
								break;
						}
						/* erasing number that has been popped */
						erasenum(&one);
						erasenum(&two);
						initnum(&one);
						initnum(&two);
						if(nisfull(&numbers)){
							cleannstack(&numbers);
							return error;
						}
						npush(&numbers, result);
					}
				}
				//printf("pushed operator\n");
				cpush(&operators, t.data.op);
				break;

			case NUMBER:
				//printf("number pushed\n");
				if(nisfull(&numbers)){
					cleannstack(&numbers);
					return error;
				}
				npush(&numbers, t.data.number);
				break;

			case END:
				while(!cisempty(&operators)){
					op = cpop(&operators);
					//printf("operator is%d\n", op);

					if(nisempty(&numbers))
						return error;
					two = npop(&numbers);
					if(nisempty(&numbers))
						return error;
					one = npop(&numbers);

					switch(op){
						case '+':
							result = add(one, two);
							break;
						case '-':
							result= sub(one, two);
							break;
						case '*':
							result = multiply(one, two);
							break;
						case '/':
							//result = divide(one, two);
							break;
						case '%':
							//result = modulo(one, two);
							break;
						default:
							return error;
							break;
					}
					/* erasing number that has been popped */
					erasenum(&one);
					erasenum(&two);
					initnum(&one);
					initnum(&two);
					npush(&numbers, result);
				}
				if(nisempty(&numbers)){
					return error;
				}
				result = npop(&numbers);
				return result;
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

void cleannstack(nstack *numbers){
	num one;
	while(!nisempty(numbers)){
		one = npop(numbers);
		erasenum(&one);
	}
	return;
}






