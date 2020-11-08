#include "read.h"

/* int readline(char **buf, int *n)
 * use:
 * 		read the line in given char array buf by dynamically allocation memory
 * precondition:
 * 		buf: pointer to the character pointer
 * 		n: int pointer 
 * postcondition:
 * 		reads the line from stdin into buf and terminate it with nul char
 * 		the total allocated size is stored in n
 */
int readline(char **buf, int *n){
	static int size = 2000;
	static int eofflag = 0;
	(*buf) = (char *)malloc(sizeof(char) * size);
	int i = 0;
	char c;
	if(eofflag)
		return EOF;
	while((c = getchar()) != '\n' && c != EOF){
		if(c == '\\'){
			c = getchar();
			printf("... ");
			continue;
		}
		if(i >= size){
			size = size + 2000;
			*buf = realloc(*buf, size);
		}
		(*buf)[i++] = c;
	}
	if(c == EOF)
		eofflag = 1;
	if(eofflag && i == 0){
		return EOF;
	}
	*n = size;
	(*buf)[i] = '\0';
	size = 2000; //line is complete so reset the size
	return i;
}
