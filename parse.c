#include "num.h"
#include "parse.h"

//enum state {START, OPERATOR, NUMBER, FRAC, END, ERR};

void insert_digit(num *, int );

token parse(char *str){
	static int i = 0;
	static int prev = START;
	int curr, count = 0;
	num number;
	int j = 0;
	char buf[DIG_LEN + 1], op;
	token t;

	if(prev == END){
		t.type = END;
		return t;
	}

	while(1){
		switch(str[i]){
			case ' ': case '\t': case '\f': case '\v':
				curr = SPACE;
				switch(prev){
					case START:
						i++;
						prev = curr;
						break;

					case OPERATOR:
						t.type = OPERATOR;
						t.data.op = op;
						prev = curr;
						i++;
						return t;
						break;

					case NUMBER: case FRAC:
						buf[j] = '\0';
						insert_digit(&number, atoi(buf)); 
						j = 0;
						prev = curr;
						break;

					case ERR:
						t.type = ERR;
						prev = curr;
						i++;
						return t;
						break;
					default:
						prev = curr;
						i++;
						break;
				}

				break;
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				curr = NUMBER;
				switch(prev){
					case START: case SPACE:
						initnum(&number);
						count = 0;
						j = 0;
						buf[j++] = str[i++];
						prev = curr;
						break;

					case OPERATOR:
						t.type = OPERATOR;
						t.data.op = op; 
						initnum(&number); //new number started
						count = 0;
						j = 0;
						buf[j++] = str[i++];
						prev = curr;
						return t;
						break;

					case NUMBER:
						if(j >= DIG_LEN){
							buf[j] = '\0';
							insert_digit(&number, atoi(buf)); 
							count++; //digit count
							j = 0;
						}
						buf[j++] = str[i++];
						prev = curr;
						break;

					case FRAC:
						buf[j] = '\0';
						insert_digit(&number, atoi(buf)); 
						count++; //digit count
						j = 0;
						t.number.point = count;
						buf[j++] = str[i++];
						prev = curr;
						break;

					case ERR:
						t.type = ERR;
						prev = curr;
						i++;
						return t;

					default:
						prev = curr;
						i++;
				}
			case '.':
				curr = FRAC;
				switch(prev){
					case START: case SPACE:
						initnum(&number);
						count = 0;
						buf[j++] = '0';
						i++;
						prev = curr;
						break;

					case OPERATOR: 
						t.type = OPERATOR;
						t.data.op = op;
						initnum(&number);
						count = 0;
						buf[j++] = '0';
						i++;
						prev = curr;
						return t;
						break;

					case FRAC: 
						t.type = ERR; //parsing error
						prev = curr;
						i++;
						return t;
						break;

					case ERR: 
						t.type = ERR;
						prev = curr;
						i++;
						return t;
						break;

					case NUMBER:
						i++;
						prev = curr;
						break;

					default:
						break;
				}
				break;
			case '+': case '-': case '*': case '/': case '%':
				curr = OPERATOR;
				switch(prev){
					case START: case SPACE:
						op = str[i++];
						prev = curr;
						break;

					case NUMBER:
						buf[j] = '\0';
						insert_digit(&number, atoi(buf)); 
						j = 0;
						op = str[i++];
						t.type = NUMBER;
						t.data.number = number;
						prev = curr;
						return t;
						break;

					case FRAC:  // this simply means number is like 123. so can ignore fraction which is zero
						buf[j] = '\0';
						insert_digit(&number, atoi(buf)); 
						j = 0;
						op = str[i++];
						t.type = NUMBER;
						prev = curr;
						t.data.num = number;
						return t;
						break;

					case ERR:
						t.type = ERR;
						op = str[i++];
						prev = curr;
						return t;
						break;

					default:
						prev = curr;
						i++;
						break;
				}
				break;
			case '\0':
				curr = END;
				switch(prev){
					case START: case SPACE:
						t.type = END;
						prev = curr;
						i++;
						return t;
						break;

					case OPERATOR:
						t.data.op = op;
						t.type = OPERATOR;
						prev = curr;
						i++;
						return t;
						break;

					case NUMBER:
						buf[j] = '\0';
						insert_digit(&number, atoi(buf)); 
						j = 0;
						t.type = NUMBER;
						t.data.num = number;
						prev = curr;
						return t;
						break;

					case FRAC:
						buf[j] = '\0';
						insert_digit(&number, atoi(buf)); 
						j = 0;
						t.type = NUMBER;
						t.data.num = number;
						prev = curr;
						return t;
						break;

					case ERR:
						t.type = ERR;
						prev = curr;
						i++;
						return t;
						break;

					default:
						prev = curr;
						i++;
						break;
				}
			default:
				break;
		}
	}
	t.type = ERR;
	return t;
}

