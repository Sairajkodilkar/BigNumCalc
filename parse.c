#include "num.h"
#include "parse.h"

//enum state {START, OPERATOR, NUMBER, FRAC, END, ERR};

void insertbuf(num *, char *, int);

token parse(char *str){
	static int i = 0;
	static int prev = START;
	static char op;
	int curr, size = 1024;
	num number;
	static int j = 0;
	static char *buf = NULL ;
	if(i == 0)
		buf = (char *)malloc(sizeof(char) * size);
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

					case NUMBER: 
						buf[j] = '\0';
						insertbuf(&number, buf, j);
						t.type = NUMBER;
						t.data.number = number;
						i++;
						j = 0;
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
				break;
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				curr = NUMBER;
				switch(prev){
					case START: case SPACE:
						initnum(&number);
						j = 0;
						buf[j++] = str[i++];
						prev = curr;
						break;

					case OPERATOR:
						t.type = OPERATOR;
						t.data.op = op; 
						initnum(&number); //new number started
						j = 0;
						buf[j++] = str[i++];
						buf[j] = '\0';
						prev = curr;
						break;

					case NUMBER:
						if(j >= size){
							size += 1024;
							buf = realloc(buf, size);
						}
						buf[j++] = str[i++];
						buf[j] = '\0';
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
			case '+': case '-': case '*': case '/': case '%':
				curr = OPERATOR;
				switch(prev){
					case START: case SPACE:
						op = str[i++];
						prev = curr;
						break;

					case NUMBER:
						buf[j] = '\0';
						insertbuf(&number, buf, j);
						j = 0;
						op = str[i++];
						t.type = NUMBER;
						t.data.number = number;
						prev = curr;
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
						insertbuf(&number, buf, j);
						j = 0;
						t.type = NUMBER;
						t.data.number = number;
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
						t.type = END;
						return t;
						break;
				}
				break;
			default:
				prev = ERR;
				t.type = ERR;
				return t;
				break;
		}
	}
	t.type = ERR;
	return t;
}


void insertbuf(num *one, char *buf, int j){
	int offset = j - DIG_LEN;
	int n;
	while(1){
		if(offset <= 0){
			offset = 0;
			n = atoi(&buf[offset]);
			insert_digit(one, atoi(&buf[offset]));
			break;
		}
		n = atoi(&buf[offset]);
		insert_digit(one, n);
		buf[offset] = '\0';
		offset -= DIG_LEN;
	}
	reverse(one);
	return;
}





