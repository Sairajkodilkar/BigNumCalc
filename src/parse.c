#include "num.h"
#include "parse.h"

//enum state {START, OPERATOR, NUMBER, FRAC, END, ERR};

void insertbuf(num *, char *, int, int);

/* NOTE :for negative to work number and sign does not have space
 * 		e.g 123 * - 123 will not work but 123 * -123 does work
 */
token parse(char *str){
	static int i = 0;
	static int prev = START;
	static int j = 0;
	static int op_flag = 2;
	static char op;
	static char *buf = NULL ;
	int curr, size = 1024;
	static num number;
	if(i == 0)
		buf = (char *)malloc(sizeof(char) * size);
	token t;

	if(prev == END){
		free(buf);
		i = 0;
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
						insertbuf(&number, buf, j, 0);
						t.type = NUMBER;
						t.data.number = number;
						i++;
						j = 0;
						prev = curr;
						return t;
						break;
						
					case FRAC:
						t.type = NUMBER;
						t.data.number = number;
						i++;
						j = 0;
						prev = curr;
						return t;

					case ERR:
						t.type = ERR;
						prev = curr;
						i++;
						return t;
						break;

					default:
						prev = ERR;
						i++;
						break;
				}
				break;
			case '0': case '1': case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				curr = NUMBER;
				switch(prev){
					case START: case SPACE:
						op_flag = 0;
						initnum(&number);
						j = 0;
						buf[j++] = str[i++];
						prev = curr;
						break;

					case OPERATOR:
						initnum(&number); //new number started
						j = 0;
						buf[j++] = str[i++];
						buf[j] = '\0';
						prev = curr;
						if(op_flag >= 2 && op == '-'){
							number.sign = -1;
							op_flag = 0;
							continue;
						}
						t.type = OPERATOR;
						t.data.op = op; 
						return t;
						break;

					case NUMBER: case FRAC:
						op_flag = 0;
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
						prev = ERR;
						i++;
						break;
				}
				break;
			case '+': case '-': case '*': case '/': case '%':
			case '(': case ')':
				curr = OPERATOR;
				op_flag += 1;
				switch(prev){
					case START: case SPACE:
						op = str[i++];
						prev = curr;
						break;

					case OPERATOR:
						t.type = OPERATOR;
						t.data.op = op;
						op = str[i];
						prev = curr;
						i++;
						return t;
						break;

					case NUMBER:
						buf[j] = '\0';
						insertbuf(&number, buf, j, 0);
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
						prev = ERR;
						i++;
						break;
				}
				break;
			case '\0':
				curr = END;
				switch(prev){
					case START: case SPACE:
						i = 0;
						free(buf);
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
						insertbuf(&number, buf, j, 0);
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
						prev = ERR;
						i++;
						t.type = ERR;
						break;
				}
				break;
			case '.':
				curr = FRAC;
				switch(prev){
					case START: case SPACE:
						initnum(&number);
						number.point = 0;
						j = 0;
						i++;
						prev = curr;
						break;

					case NUMBER:
						buf[j] = '\0';
						insertbuf(&number, buf, j, 1);
						j = 0;
						i++;
						prev = curr;
						break;
						
					case OPERATOR:
						initnum(&number);
						number.point = 0;
						j = 0;
						i++;
						prev = curr;
						t.data.op = op;
						t.type = OPERATOR;
						return t;
						break;

					case ERR:
						t.type = ERR;
						prev = curr;
						i++;
						return t;
						break;

					default:
						prev = ERR;
						i++;
						t.type = ERR;
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


void insertbuf(num *one, char *buf, int j, int frac){
	int offset = j % DIG_LEN, x = 0, count = 0, n, flag = 0;
	offset = (offset == 0 || one->point != -1) ? DIG_LEN : offset;
	char ch;
	if(offset > j && one->point != -1){ //point != -1 handles the fraction  condition
		offset = j;
		flag = 1;
	}
	while(offset <= j){
		ch = buf[offset];
		buf[offset] = '\0';
		n = atoi(buf + x);
		if(offset == j && one->point != -1 && n != 0){
			while(n < (MAX_DIG + 1))
				n = n * 10;
			n = n / 10;
		}
		insert_digit(one, n);
		count++;
		buf[offset] = ch;
		x = offset;
		offset += DIG_LEN;
		if(flag)
			break;
		if(offset > j && one->point != -1){
			offset = j;
			flag = 1;
		}
	}
	if(frac == 1){ //this number of digit are before fraction
		one->point = count;
	}

	return;
}




