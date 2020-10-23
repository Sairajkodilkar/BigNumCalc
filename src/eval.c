#include "eval.h"

enum precedence {LOW, EQUAL, ADDSUB, MULDIV, MODULO, BRACKET};

void cleannstack(nstack *);
/* TODO division operation is pending */
num eval(char *str){
	nstack numbers;
	cstack operators;

	token t;
	num result, one, two, error;

	static num memory[26];
	static int storage;

	int currpre = LOW, prevpre, bracket = 0; 
	char op;

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
				switch(t.data.op){
					case '+': case '-':
						currpre = ADDSUB + bracket;
						break;
					case '*': case '/':
						currpre = MULDIV + bracket;
						break;
					case '%':
						currpre = MODULO + bracket;
						break;
					case '=':
						ipush(&address, storage); //if equal to is encountered storage is pushed on address stack
						currpre = EQUAL + bracket;
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
							case "=":
								storage = ipop(&address);
								copy(two, memory + storage);
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
				cpush(&operators, t.data.op);
				break;

			case NUMBER:
				if(nisfull(&numbers)){
					cleannstack(&numbers);
					return error;
				}
				npush(&numbers, t.data.number);
				break;

			case VAR:
				/*
				 * push var on num stack
				 */
				storage = t.data.op - 'a';
				copy(memory[storage], &one);
				npush(&numbers, one);
				break;

			case END:
				if(bracket != 0)
					return error;
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
						case "=":
							storage = pop(&address);
							copy(two, memory + storage);
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
				if(nisempty(&numbers) || bracket != 0){
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



