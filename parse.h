#ifndef _PARSE
#define _PARSE

#include <stdio.h>
#include <stdlib.h>
#include <limit.h>
#include <string.h>
#include "num.h"

typedef struct token{
	int type;
	union{
		num number;
		char op;
	}data;
}token;

token getnext(char *string);

#endif 
