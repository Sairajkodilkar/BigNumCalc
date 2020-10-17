#include "read.h"

/* int readline(char *buf, int n)
 * use:
 * 		read the line in given char array buf of size n
 * precondition:
 * 		buf: character array
 * 		n: max size of array
 * postcondition:
 * 		reads the line from stdin into buf and terminate it with nul char
 * 		if input is greater than size of buf then n - 1 chars read and terminated by nul
 */
int readline(char *buf, int n){
	int i = 0;
	char c;
	while((((c = getchar()) != '\n') || c != EOF) && i < n - 1){
		buf[i++] = c;
	}
	buf[i] = '\0';
	return i;
}
